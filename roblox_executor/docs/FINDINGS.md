# Roblox Luau Executor — Findings So Far

Клиент: `version-117ad38284844374` (== `version-9ac8595712b447a7`)
Платформа: Windows 25H2 x64
Дата: 2026-10-22

## Что уже сделано

1. **Распакован образ** через pe-sieve `/dmode 3` после warmup'а в Studio-игре.
   Результат: `C:\Users\Zumhad\Desktop\d\dump2\process_<pid>\7ff67cc60000.RobloxPlayerBeta.exe`
   (~152 MB).
2. **IDA64 анализ + rebase to 0.**
3. **Валидация оригинального `.hpp`** через скрипт `validate_hpp.py` на двух дампах.
   - До warmup: 81 VALID / 33 ZEROS
   - После warmup: 88 VALID / 26 ZEROS
4. **Ручная валидация** через декомпайл с переименованиями:
   - `luaG_runerror`
   - `luaD_throw` + новый `lua_exception::ctor`
   - `InstanceBridge::Index/NewIndex/UserdataNamecall` + capability thresholds
   - `ScriptContext::Resume`
   - `GetGlobalState` → encrypted pointer scheme
   - `Luau_Load`
   - `Luau_Execute_Dispatcher` + `Interpreter` + `Native`
   - `lua_checkstack` → struct offsets lua_State
   - `CallInternal` → полный layout lua_State / CallInfo / Closure

## Файлы

- `Internal_Offsets_updated.hpp` — обновлённый hpp со статусами и новыми функциями
- `RobloxStructs.hpp` — struct layouts

## Важные открытия для executor'а

### 1. `global_State*` зашифрован

Прямое чтение указателя даст мусор. Схема:

```cpp
void* holder   = call sub_42DD7C0(ScriptContext* + 0x1A8)
uint64_t enc   = *(uint64_t*)(holder + 0x18)
uint32_t klo   = *(uint32_t*)(holder + 0x00)
uint32_t khi   = *(uint32_t*)(holder + 0x04)
uint64_t gs    = enc XOR ((uint64_t)khi << 32 | klo)
```

### 2. Execute dispatcher выбирает JIT или interpreter

```cpp
if (L[0x05]) Luau_Execute_Native(L);
else          Luau_Execute_Interpreter(L);
```

Для executor'а безопаснее выставить `L[0x05] = 0` → всегда interpreter.

### 3. Identity сидит в TLS slot 0x20

Каждый InstanceBridge-метаметод в прологе:
```asm
mov edx, 20h
mov rax, gs:58h          ; TEB->TLS pointer
mov rcx, [rax]
mov eax, [rdx+rcx]       ; TLS[0x20] = identity
cmp cs:threshold, eax
jg error_path
```

### 4. Capability thresholds лежат в непрерывной таблице

- `0x8F42E10` — threshold для NewIndex
- `0x8F42DE0` — threshold для Namecall

Они на 0x30 apart → **есть таблица thresholds по операциям**. Для полноты надо декомпилировать и остальные bridge-методы и собрать всю таблицу.

### 5. Luau_Load принимает struct, не flat args

```cpp
struct RobloxLoadInfo {
    uint8_t  pad[0x30];
    char*    chunkname;    // +0x30
    uint8_t* data;         // +0x38
    uint64_t field_40;     // +0x40
    uint32_t size;         // +0x48
};
int Luau_Load(lua_State* L, RobloxLoadInfo* info);
```

Не стандартная `luau_load(L, name, data, size, env)` — обёртка через struct.

## Что осталось сделать

### Критично
- [ ] global_State offsets (mainthread, strt, l_registry, cb, ptrenckey)
- [ ] Proto layout (k, code, sizek, sizecode, nups, numparams, maxstacksize)
- [ ] Table layout (metatable, array, node, sizearray)
- [ ] Полная таблица capability thresholds (не только 2 найденные)
- [ ] Luau opcode mapping (из switch/jump table в Luau_Execute_Interpreter)

### Важно
- [ ] AOB signatures для всех найденных функций
- [ ] Encryption keys XOR для `L+0x80` (stacksize_enc)
- [ ] Instance vftable decrypt routine
- [ ] Instance struct offsets (Children, Parent, Name, ClassDescriptor)
- [ ] Разобрать `sub_42DD7C0` (holder getter) — вторичная encryption

### Nice to have
- [ ] Передамп с полным pre-touch всех executable pages (через твой r/w driver)
- [ ] Live memory scanner который находит offsets по signatures каждый запуск
- [ ] Autodumper (hpp + Structs.hpp генератор)

## Структура Executor'а (следующий этап)

```
┌─────────────────────────────────────────┐
│ Dumper (external process)                │
│  - читает память RobloxPlayerBeta        │
│  - находит TaskScheduler → main L*       │
│  - находит ScriptContext → GetGlobalState│
│  - читает identity из TLS                │
│  - выдаёт JSON offsets                   │
└─────────────────────────────────────────┘
             │
             ↓
┌─────────────────────────────────────────┐
│ Loader (через r/w driver)                │
│  - подкладывает bytecode в LoadInfo      │
│  - вызывает Luau_Load                    │
│  - настраивает identity = 8              │
│  - вызывает ScriptContext::Resume или    │
│    напрямую Luau_Execute_Dispatcher      │
└─────────────────────────────────────────┘
             │
             ↓
┌─────────────────────────────────────────┐
│ Compiler (host)                          │
│  - форк luau с github                    │
│  - .lua source → bytecode                │
│  - передаёт loader'у                     │
└─────────────────────────────────────────┘
```

## Что добавилось в итерации 2 (22 октября)

### global_State offsets (из GcStep)
- `mainthread` at +0x1A0 — ⭐ ключ к получению главного lua_State*
- Полная карта GC полей (gray, grayagain, totalbytes, sweep lists, gcstate)
- Alloc/free hook callbacks на +0x6A8, +0x6C0
- Memory per category: +0x2DB0 + 8*memcat

### Proto layout partial (из luaF_newproto)
- sizeof = 216 bytes
- CommonHeader confirmed (marked, memcat, tt=15)
- 9 pointer fields identified но точные имена (k/code/p/...) не маппнуты
- Поле +0x68 инициализируется НЕГАТИВНЫМ значением — encrypted (вероятно codeentry)

### Luau opcode system (из Luau_Execute_Interpreter prologue)
- RemapTable at 0x26D6DE4 (uint8_t[256]) — encoded_byte → canonical_idx
- JumpTable at label jpt_26CA3B4 (нужно резолвить реальный адрес через IDA)
- 94 distinct encoded opcodes в этой версии
- Canonical index 94 = "invalid/default" handler slot
- Полная таблица encoded→canonical сохранена в OPCODES.md + opcode_remap_*.txt

### Confirmed additionals через Execute_Interpreter prologue
- global_State+0x6E8 = JIT dispatch function pointer
- CallInfo+0x08 — chain pointer (не pad, как думали)
- CallInfo flags bit 4 = "JIT entry"

## Следующий конкретный шаг

1. Резолвить реальный адрес `jpt_26CA3B4` в IDA → получить RVA handler'ов
2. Pattern-match handler'ов к luau upstream `OP_*` → полный opcode decode
3. Mapping Proto pointer fields (0x08, 0x10, 0x20, ...) → k/code/p/... через Luau_Load
4. Encryption scheme для Proto::codeentry — найти XOR routine
5. Scaffold C++ dumper с r/w driver и генерацией структур в runtime
