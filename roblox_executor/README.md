# Roblox Luau Executor — Research & Dumper

Персональный research проект по реверсу Roblox client (Luau VM, Instance bridge,
scheduler) и построению dumper'а offset'ов для написания standalone executor'а.

**Target:** `RobloxPlayerBeta.exe` version-117ad38284844374
**Платформа:** Windows 25H2 x64
**Статус:** research phase — struct extraction в процессе

## Структура

```
roblox_executor/
├── include/
│   ├── Internal_Offsets.hpp    — все найденные function RVAs со статусами
│   └── RobloxStructs.hpp       — struct offsets (lua_State, CallInfo, Closure,
│                                  Proto, global_State, ScriptContext, GSHolder)
├── docs/
│   ├── FINDINGS.md             — итог проделанной работы и план
│   ├── OPCODES.md              — Luau opcode system и как её декодить
│   └── opcode_remap_*.txt      — сырые dump'ы opcode remap table по версиям
└── scripts/
    ├── validate_hpp.py         — IDA Python: валидация hpp против текущей базы
    └── dump_opcodes.py         — IDA Python: вытаскивает opcode mapping
```

## Что уже сделано

- Распакован образ через pe-sieve после warmup'а в Studio-игре
- 88 функциональных offset'ов валидированы в IDA через `validate_hpp.py`
- Вручную подтверждены ключевые: luaG_runerror, luaD_throw, Luau_Load,
  Luau_Execute_Dispatcher/Interpreter/Native, GetGlobalState, ScriptContext_Resume,
  InstanceBridge_Index/NewIndex/UserdataNamecall, CallInternal, lua_checkstack
- Struct offsets: полный lua_State, CallInfo, Closure, partial Proto, полный global_State
- Encryption scheme для global_State pointer задокументирована
- Opcode remap table dump (94 encoded opcodes этой версии)

## Что осталось (критично)

- Proto pointer field mapping (0x08 → k? code? p?)
- Jump table резолв для получения handler RVAs
- Encryption key для Proto::codeentry (+0x68)
- Полная таблица capability thresholds (сейчас 2 из N)
- Table / TString / Udata layouts
- C++ dumper который читает через r/w driver и генерирует структуры runtime

Смотри `docs/FINDINGS.md` для полного плана.
