// =============================================================================
//  RobloxStructs.hpp
//  Внутренние структуры Roblox Luau VM
//  Версия клиента: version-117ad38284844374 (== version-9ac8595712b447a7)
//  Платформа: Windows 25H2 x64
//  Извлечено: 2026-10-22
//
//  Источник оффсетов: ручной реверс в IDA Pro на распакованном
//  RobloxPlayerBeta.exe (pe-sieve /dmode 3), декомпайл функций
//  lua_checkstack, CallInternal, GetGlobalState, Luau_Load.
//
//  Статус полей:
//    [c] confirmed  — валидировано хотя бы в одной функции
//    [i] inferred   — выведено по контексту, не подтверждено прямым чтением
//    [?] unknown    — padding / неизвестное поле
// =============================================================================
#pragma once
#include <cstdint>

namespace RobloxStructs {

// ---------------------------------------------------------------------------
// Константы VM
// ---------------------------------------------------------------------------
constexpr size_t SIZEOF_TVALUE    = 0x10;   // 16 байт (shift 4 в lua_checkstack)
constexpr size_t SIZEOF_CALLINFO  = 0x30;   // 48 байт (инкремент ci в CallInternal)
constexpr int    LUAI_MAXCCALLS   = 200;    // cmp 200 в CallInternal
constexpr int    LUAI_MAXCSTACK   = 8000;   // cmp 8000 в lua_checkstack

// ---------------------------------------------------------------------------
// lua_State offsets
// ---------------------------------------------------------------------------
namespace lua_State {
    constexpr uintptr_t tt_or_flags   = 0x00;   // [c] байт флагов (test & 4 в CallInternal)
    constexpr uintptr_t activememcat  = 0x01;   // [i] memory category
    constexpr uintptr_t pad02         = 0x02;   // [?]
    constexpr uintptr_t status        = 0x03;   // [c] LUA_OK=0 / YIELD=1 / ERRRUN=6 / BREAK=127
    constexpr uintptr_t pad04         = 0x04;   // [?]
    constexpr uintptr_t isJit         = 0x05;   // [c] 0=interpreter / 1=native execute path
    constexpr uintptr_t singlestep    = 0x06;   // [i] используется в CallInternal manipulation
    constexpr uintptr_t pad07         = 0x07;   // [?]
    constexpr uintptr_t pad08         = 0x08;   // [?]
    constexpr uintptr_t end_ci        = 0x10;   // [c] CallInfo* — конец массива CI
    constexpr uintptr_t base_ci       = 0x18;   // [c] CallInfo* — начало массива CI (переаллоцируется)
    constexpr uintptr_t nCcalls       = 0x20;   // [c] uint16, max 200
    constexpr uintptr_t baseCcalls    = 0x22;   // [i] uint16
    constexpr uintptr_t pad24         = 0x24;   // [?]
    constexpr uintptr_t pad28         = 0x28;   // [?]
    constexpr uintptr_t pad30         = 0x30;   // [?]
    constexpr uintptr_t pad38         = 0x38;   // [?]
    constexpr uintptr_t pad40         = 0x40;   // [?]
    constexpr uintptr_t pad48         = 0x48;   // [?]
    constexpr uintptr_t ci            = 0x50;   // [c] CallInfo* — текущий CI
    constexpr uintptr_t base          = 0x58;   // [c] StkId — база текущего фрейма
    constexpr uintptr_t stack         = 0x60;   // [c] StkId — stack base
    constexpr uintptr_t stack_last    = 0x68;   // [c] StkId — конец стека
    constexpr uintptr_t top           = 0x70;   // [c] StkId — верх стека
    constexpr uintptr_t global        = 0x78;   // [c] global_State*
    constexpr uintptr_t stacksize_enc = 0x80;   // [c] int32 — ВНИМАНИЕ: encrypted
                                                //     real_size = *stacksize_enc XOR (uint32_t)(L+0x80)
    constexpr uintptr_t size_ci       = 0x84;   // [c] int32
};

// ---------------------------------------------------------------------------
// CallInfo offsets (sizeof = 0x30)
// ---------------------------------------------------------------------------
namespace CallInfo {
    constexpr uintptr_t base      = 0x00;   // [c] StkId — base of frame
    constexpr uintptr_t pad08     = 0x08;   // [?]
    constexpr uintptr_t func      = 0x10;   // [c] StkId — pointer на функцию в стеке
    constexpr uintptr_t top       = 0x18;   // [c] StkId — top для этого frame
    constexpr uintptr_t savedpc   = 0x20;   // [c] void* — сохранённый PC
    constexpr uintptr_t nresults  = 0x28;   // [c] int32 — ожидаемое число результатов
    constexpr uintptr_t flags     = 0x2C;   // [c] int32 — флаги фрейма
};

// ---------------------------------------------------------------------------
// Closure offsets
// ---------------------------------------------------------------------------
namespace Closure {
    constexpr uintptr_t pad00_header = 0x00;   // [?] GCObject header (tt, marked)
    constexpr uintptr_t isC          = 0x03;   // [c] 1 = C closure / 0 = Lua closure
    constexpr uintptr_t stacksize    = 0x06;   // [c] uint8 — maxstacksize (используется как 16 * stacksize)
    constexpr uintptr_t pad08        = 0x08;   // [?]
    constexpr uintptr_t pad10        = 0x10;   // [?]
    // for Lua closure (isC == 0):
    constexpr uintptr_t proto_or_env = 0x18;   // [c] Proto* — тело функции
};

// ---------------------------------------------------------------------------
// global_State offsets (из GcStep + CallInternal)
// ---------------------------------------------------------------------------
namespace global_State {
    constexpr uintptr_t strt_nuse       = 0x008;   // [c] int32 — string table used count
    constexpr uintptr_t strt_size       = 0x00C;   // [c] int32 — string table size
    constexpr uintptr_t currentwhite    = 0x010;   // [c] uint8 — текущий GC white
    constexpr uintptr_t gcstate         = 0x011;   // [c] uint8 — GC state (1-4 в GcStep switch)
    constexpr uintptr_t frealloc        = 0x020;   // [c] lua_Alloc — функция аллокатора
    constexpr uintptr_t allocud         = 0x028;   // [c] void* — ud для аллокатора
    constexpr uintptr_t gray            = 0x030;   // [c] GCObject* — gray list head
    constexpr uintptr_t grayagain       = 0x038;   // [c] GCObject* — second gray list
    constexpr uintptr_t totalbytes      = 0x050;   // [c] size_t — всего выделено
    constexpr uintptr_t mainthread      = 0x1A0;   // [c] lua_State* — ⭐ ГЛАВНЫЙ ТРЕД
    constexpr uintptr_t sweepgc_list1   = 0x310;   // [c] GCObject* — sweep state A
    constexpr uintptr_t sweepgc_list2   = 0x4B8;   // [c] GCObject* — sweep state B
    constexpr uintptr_t alloc_hook      = 0x6A8;   // [c] void(*)(...) — alloc callback
    constexpr uintptr_t free_hook       = 0x6C0;   // [c] void(*)(...) — free callback
    // memory per category: base + 8 * memcat (из CallInternal v16[v87+1462])
    constexpr uintptr_t memcats_base    = 0x2DB0;  // [c] uint64[64] — байт per memcat
    // GC timing / accumulators
    constexpr uintptr_t gc_stat_ts_a    = 0x4AC0;
    constexpr uintptr_t gc_stat_ts_b    = 0x4AE0;
    constexpr uintptr_t gc_stat_c       = 0x4C40;
    constexpr uintptr_t gc_stat_d       = 0x4C48;
    constexpr uintptr_t gc_accum_a      = 0x4CA8;
    constexpr uintptr_t gc_accum_b      = 0x4CB0;
    constexpr uintptr_t gc_debt_a       = 0x4CB8;
    constexpr uintptr_t gc_debt_b       = 0x4CC0;
};

// ---------------------------------------------------------------------------
// ⭐ Как получить главный lua_State* для executor'а (external, без call)
// ---------------------------------------------------------------------------
//   1. void*    ctx    = /* найти ScriptContext через TaskScheduler / DataModel */;
//   2. uint8_t* holder = (uint8_t*)ctx + ScriptContext::gs_holder_default;  // +0x40
//   3. uint64_t enc    = *(uint64_t*)(holder + GSHolder::encrypted_ptr);    // +0x18
//   4. uint32_t klo    = *(uint32_t*)(holder + GSHolder::key_low);          // +0x00
//   5. uint32_t khi    = *(uint32_t*)(holder + GSHolder::key_high);         // +0x04
//   6. uint64_t gs_raw = enc ^ (((uint64_t)khi << 32) | klo);
//   7. global_State* gs = (global_State*)gs_raw;
//   8. lua_State* mainL = *(lua_State**)((uint8_t*)gs + global_State::mainthread);  // +0x1A0
//
// Дальше mainL — точка входа во всё:
//   L[0x70] = top         (куда push'ить TValue)
//   L[0x50] = ci          (текущий CallInfo)
//   L[0x78] = gs          (back-ref)
//   L[0x05] = isJit flag  (выставить 0 для interpreter)
//   L[0x03] = status      (0 = ok)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// ScriptContext offsets (из GetGlobalState + ScriptContext_GetGSHolder)
// ---------------------------------------------------------------------------
namespace ScriptContext {
    constexpr uintptr_t state_field          = 0x1548;  // [c] int32 — состояние (cmp 3 → crash)
    constexpr uintptr_t gs_holder_arg_offset = 0x1A8;   // [c] передаётся как arg в getter

    // Из sub_42DD7C0 (ScriptContext_GetGSHolder):
    // Два встроенных holder'а по 688 байт идут подряд:
    //   ScriptContext + 0x40 (= 64)   — default holder (для обычного identity)
    //   ScriptContext + 0x2F0 (= 752) — elevated holder (identity_bit=1)
    //
    // Выбор зависит от: (GetCapabilities(thread) >> 3) & 1
    // Для dumper'а без идентификации — всегда ReadDefault holder на +0x40.
    constexpr uintptr_t gs_holder_default    = 0x040;   // [c] default identity holder (688 bytes)
    constexpr uintptr_t gs_holder_elevated   = 0x2F0;   // [c] elevated identity holder (688 bytes)
    constexpr size_t    gs_holder_size       = 688;     // [c] sizeof каждого holder'а

    // Hash-table для non-default thread-specific holder'ов (FNV-1a):
    //   ScriptContext + 0x5A0 (= 1440) — hash buckets для identity=0
    //   ScriptContext + 0x600 (= 1536) — hash buckets для identity=1
    // Bucket struct = 96 bytes. Для MVP dumper'а не нужны.
    constexpr uintptr_t hash_table_normal    = 0x5A0;
    constexpr uintptr_t hash_table_elevated  = 0x600;
    constexpr size_t    hash_bucket_size     = 96;
    constexpr uint64_t  FNV_PRIME            = 0x100000001B3;
    constexpr uint64_t  FNV_BASIS            = 0xCBF29CE484222325;
};

// ---------------------------------------------------------------------------
// global_State pointer encryption (из GetGlobalState)
// ---------------------------------------------------------------------------
// Как получить global_State* из ScriptContext:
//   holder     = call sub_42DD7C0(scriptContext + 0x1A8)
//   gs_encrypted = *(uint64_t*)(holder + 0x18)
//   key_low    = *(uint32_t*)(holder + 0x00)
//   key_high   = *(uint32_t*)(holder + 0x04)
//   gs_real    = gs_encrypted XOR ((key_high << 32) | key_low)
namespace GSHolder {
    constexpr uintptr_t key_low        = 0x00;   // [c] uint32 XOR key low
    constexpr uintptr_t key_high       = 0x04;   // [c] uint32 XOR key high
    constexpr uintptr_t encrypted_ptr  = 0x18;   // [c] uint64 encrypted global_State*
};

// ---------------------------------------------------------------------------
// Luau_Load struct (LoadInfo) — передаётся как rdx в Luau_Load
// ---------------------------------------------------------------------------
namespace LoadInfo {
    constexpr uintptr_t pad00         = 0x00;   // [?]
    constexpr uintptr_t field_18      = 0x18;   // [c] используется в lea rax, [rdx+18h]
    constexpr uintptr_t chunkname     = 0x30;   // [i] char*
    constexpr uintptr_t data          = 0x38;   // [c] uint8_t* — байткод
    constexpr uintptr_t field_40      = 0x40;   // [c] неизвестно
    constexpr uintptr_t size          = 0x48;   // [c] uint32 — размер байткода
};

// ---------------------------------------------------------------------------
// Identity / TLS
// ---------------------------------------------------------------------------
namespace Identity {
    constexpr uintptr_t TLS_SLOT      = 0x20;   // [c] TLS slot индекс для thread identity
                                                //     (из InstanceBridge metamethods: edx, 20h)
};

// ---------------------------------------------------------------------------
// Luau status values (из CallInternal: v70 == 1 || v70 == 6 || v70 == 127)
// ---------------------------------------------------------------------------
enum LuaStatus : uint8_t {
    LUA_OK       = 0,
    LUA_YIELD    = 1,
    LUA_ERRRUN   = 6,     // [c] совпадает с luaD_throw(L, 2) → по хронологии
                          //     и luaG_runerror → LUA_ERRRUN
    LUA_BREAK    = 127,   // [c] roblox-specific
};

// ---------------------------------------------------------------------------
// Proto layout (из luaF_newproto, sizeof = 216 = 0xD8)
// Статус: WIP — pointer fields инициализируются self-reference pattern'ом,
// точный маппинг offset→имя поля требует cross-ref через Luau_Load.
// ---------------------------------------------------------------------------
namespace Proto {
    // CommonHeader
    constexpr uintptr_t marked         = 0x00;   // [c] uint8 — GC color
    constexpr uintptr_t memcat         = 0x01;   // [c] uint8 — memory category
    constexpr uintptr_t tt             = 0x02;   // [c] uint8 — type tag = 15 (LUA_TPROTO)
    constexpr uintptr_t flags_or_pad   = 0x03;   // [c] uint32 — flags/pad

    // Pointer fields (все инициализируются self-ref — encrypted/custom scheme)
    constexpr uintptr_t ptr_08         = 0x08;   // [i] likely k (constants)
    constexpr uintptr_t ptr_10         = 0x10;   // [i] likely code (bytecode)
    constexpr uintptr_t ptr_20         = 0x20;   // [i] likely p (child protos)
    constexpr uintptr_t ptr_38         = 0x38;   // [i] likely lineinfo
    constexpr uintptr_t ptr_40         = 0x40;   // [i] likely abslineinfo
    constexpr uintptr_t ptr_58         = 0x58;   // [i] likely locvars
    constexpr uintptr_t ptr_60         = 0x60;   // [i] likely upvalues
    constexpr uintptr_t ptr_68_enc     = 0x68;   // ⚠ [c] NEGATED on init — ENCRYPTED (возможно codeentry/source)
    constexpr uintptr_t ptr_80         = 0x80;   // [i] additional pointer field

    constexpr size_t    SIZEOF         = 0xD8;   // 216 bytes
};

// ---------------------------------------------------------------------------
// Luau opcode table addresses
// ---------------------------------------------------------------------------
namespace Opcodes {
    constexpr uintptr_t RemapTable_RVA   = 0x26D6DE4;    // [c] uint8_t[256]
    // JumpTable: label jpt_26CA3B4 в IDA (резолвить через name lookup)
    constexpr size_t    CanonicalCount   = 94;
    constexpr uint8_t   InvalidIndex     = 94;           // индекс "default" handler'а
};

} // namespace RobloxStructs
