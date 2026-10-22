// =============================================================================
//  Internal_Offsets.hpp  (updated 2026-10-22)
//  version-117ad38284844374 == version-9ac8595712b447a7
//
//  Статусы (из validate_hpp.py прогона):
//    ✓ VALID       — функция подтверждена в IDA, prologue правильный
//    ✓ DATA_OK     — не функция, но данные/pointer на месте
//    ⚠ NEEDS_WARM  — страница холодная в dump'е (ищи заново, или живи без неё)
//    ★ NEW         — новая находка, не было в оригинальном hpp
// =============================================================================
#pragma once
#include <cstdint>
#include <string>
#include <windows.h>

#define REBASE(addr) (addr + reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)))

inline std::string ClientVersion = "version-117ad38284844374";

namespace Offsets
{
    // --- core ---
    const uintptr_t Print                                = REBASE(0x1D071A0);  // ✓ VALID
    const uintptr_t InvokeServer                         = REBASE(0x35B1B60);  // ✓ VALID
    const uintptr_t FireServer                           = REBASE(0x34DE9B0);  // ✓ VALID
    const uintptr_t FireClient                           = REBASE(0x34DEB50);  // ✓ VALID
    const uintptr_t FireAllClients                       = REBASE(0x34DEDA0);  // ✓ VALID
    const uintptr_t EnableLoadModule                     = REBASE(0x8A21BF0);  // ⚠ NEEDS_WARM
    const uintptr_t TaskScheduler                        = REBASE(0x8F026A8);  // ✓ DATA (pointer)
    const uintptr_t TaskSchedulerTargetFps               = REBASE(0x876CB58);  // ⚠ NEEDS_WARM
    const uintptr_t KTable                               = REBASE(0x85EAD60);  // ✓ DATA
    const uintptr_t GetGlobalState                       = REBASE(0x425F7A0);  // ✓ VALID (расшифровывает encrypted ptr)
    const uintptr_t GetLuaState                          = REBASE(0x425F7A0);  // ✓ VALID (= GetGlobalState)
    const uintptr_t CastArgs                             = REBASE(0x41C68B0);  // ✓ VALID
    const uintptr_t PushInstance                         = REBASE(0x4246E90);  // ✓ VALID
    const uintptr_t InstanceNew                          = REBASE(0x436EAE0);  // ⚠ NEEDS_WARM
    const uintptr_t InstanceFindFirstChild               = REBASE(0x529340);   // ⚠ NEEDS_WARM
    const uintptr_t InstanceFindFirstChildOfClass        = REBASE(0x525F10);   // ⚠ NEEDS_WARM
    const uintptr_t InstanceFindFirstAncestorWhichIsA    = REBASE(0x525C30);   // ⚠ NEEDS_WARM
    const uintptr_t InstanceGetChildren                  = REBASE(0x526F50);   // ⚠ NEEDS_WARM

    namespace Identity {
        const uintptr_t GetCapabilities                  = REBASE(0x1D45E30);  // ✓ VALID
        const uintptr_t PrintIdentity                    = REBASE(0x43078E0);  // ⚠ NEEDS_WARM
        const uintptr_t TLS_Slot_get                     = REBASE(0x6BB0);     // ✓ VALID
        const uintptr_t Impersonator                     = REBASE(0x1D45EF0);  // ✓ VALID
    };

    namespace RobloxThread {
        const uintptr_t IdentityPtr                      = REBASE(0x86D8748);  // ✓ DATA
    };

    namespace Bytecode {
        const uintptr_t VerificationTableA               = REBASE(0x87637B0);  // ✓ DATA
    };

    namespace LuaError {
        const uintptr_t luaL_error                       = REBASE(0x26999F0);  // ✓ VALID
        const uintptr_t readonlyerror                    = REBASE(0x26B6D60);  // ✓ VALID
        const uintptr_t methoderror                      = REBASE(0x26B6D20);  // ✓ VALID
        const uintptr_t indexerror                       = REBASE(0x26B6C20);  // ✓ VALID
        const uintptr_t ordererror                       = REBASE(0x26B6BA0);  // ✓ VALID
        const uintptr_t forerrorL                        = REBASE(0x26B6A70);  // ✓ VALID
    };

    namespace Native {
        const uintptr_t DestroyString                    = REBASE(0x76AE10);   // ✓ VALID
    };

    namespace ExtraSpace {
        constexpr uintptr_t RequireBypass                = 0x988;
        constexpr uintptr_t IsCoreScript                 = 0x150;
    };

    namespace TaskDefer {
        const uintptr_t TaskWait                         = REBASE(0x43C4450);  // ✓ VALID
        const uintptr_t TaskSynchronize                  = REBASE(0x43C27B0);  // ✓ VALID
        const uintptr_t TaskDesynchronize                = REBASE(0x43C2C80);  // ✓ VALID
        const uintptr_t TaskDefer                        = REBASE(0x43C38D0);  // ✓ VALID
        const uintptr_t TaskSpawn                        = REBASE(0x43C3DB0);  // ✓ VALID
        const uintptr_t TaskDelay                        = REBASE(0x43C4150);  // ✓ VALID
    };

    namespace ScriptContext {
        const uintptr_t Resume                           = REBASE(0x43004B0);  // ✓ VALID (главный executor entry)
        const uintptr_t GetGSHolder                      = REBASE(0x42DD7C0);  // ★ NEW holder getter
        const uintptr_t GetThreadsCount                  = REBASE(0x425F800);  // ★ NEW const member — метрика "threads"
        const uintptr_t RegisterStats                    = REBASE(0x43CA2F0);  // ★ NEW регистратор метрик (disabled/threads/AverageGcTime)

        // RTTI данные
        const uintptr_t RTTI_TypeDescriptor              = REBASE(0x84F3090);  // ★ NEW ".?AVScriptContext@RBX@@" type descriptor
        const uintptr_t RTTI_COL_Primary                 = REBASE(0x786B1A8);  // ★ NEW primary COL (offset=0)
        const uintptr_t RTTI_COL_Secondary               = REBASE(0x786AFE0);  // ★ NEW secondary COL (offset=152)

        // ⭐ VTABLE — ключ для поиска instance'а в heap через scan
        const uintptr_t VTable_Primary                   = REBASE(0x70D1370);  // ★ NEW
        const uintptr_t VTable_Secondary                 = REBASE(0x70D15D8);  // ★ NEW
    };

    // ★ NEW: RBX::Lua::WeakThreadRef — wrapper объект для lua_State
    // Scan heap на qword == этот vtable → все thread wrapper'ы в процессе.
    // Из WeakThreadRef_lock извлечён layout:
    //   +0x00: vtable_ptr
    //   +0x10: wrapped target (lua_State* или RBX::Lua::Thread wrapper)
    //   +0x18: shared_ptr control block (use_count на +0x08)
    namespace WeakThreadRef {
        const uintptr_t RTTI_TypeDescriptor              = REBASE(0x8271520);  // ".?AVWeakThreadRef@Lua@RBX@@"
        const uintptr_t RTTI_COL_Primary                 = REBASE(0x7591218);  // offset=0, primary
        const uintptr_t VTable                           = REBASE(0x6E8B508);  // ⭐ scan ключ
        const uintptr_t Lock                             = REBASE(0xCF08A0);   // ★ shared_ptr lock()
        constexpr uintptr_t wrapped_target               = 0x10;               // ★ target pointer
        constexpr uintptr_t control_block                = 0x18;               // ★ shared_ptr control
        // Inheritance: public RBX::Lua::WeakObjectRef, rbx::quick_intrusive_ptr_target<WeakThreadRef>
    };

    namespace RbxTransport {
        const uintptr_t ClientRtti                       = REBASE(0x7811B28);  // ✓ DATA
        const uintptr_t AppRtti                          = REBASE(0x7775F50);  // ✓ DATA
        const uintptr_t ClientChannelConfig              = REBASE(0x3B1E5B0);  // ✓ VALID
        const uintptr_t AppReceive                       = REBASE(0x21C0120);  // ✓ VALID
        const uintptr_t AppReceiveMaxBytes               = REBASE(0x21C09D0);  // ✓ VALID
        const uintptr_t StreamCreate                     = REBASE(0x53B4350);  // ✓ VALID
        const uintptr_t StreamAppend                     = REBASE(0x21C7A10);  // ✓ VALID
        const uintptr_t StreamDestroy                    = REBASE(0x218AFF0);  // ✓ VALID
    };

    namespace Luau {
        const uintptr_t LoadModule                       = REBASE(0x42560B0);  // ⚠ NEEDS_WARM (wrapper)
        const uintptr_t LuaVM_Load                       = REBASE(0x42560B0);  // ⚠ NEEDS_WARM
        const uintptr_t Luau_Load                        = REBASE(0x26F4750);  // ✓ VALID (DATA_OK — байты живые)
        const uintptr_t Luau_Execute_Dispatcher          = REBASE(0x26BCFD0);  // ✓ VALID (dispatcher)
        const uintptr_t Luau_Execute_Interpreter         = REBASE(0x26CA240);  // ✓ VALID (interpreter)
        const uintptr_t Luau_Execute_Native              = REBASE(0x26BD7E0);  // ★ NEW — JIT path
        const uintptr_t LuaD_Throw                       = REBASE(0x2691F10);  // ✓ VALID
        const uintptr_t lua_exception_ctor               = REBASE(0x2691D80);  // ★ NEW — lua_exception::ctor(this, L, status)
        const uintptr_t luaC_step                        = REBASE(0x26B0B80);  // ✓ VALID
        // Старый alias Luau_Execute устарел — используй Luau_Execute_Dispatcher
    };

    namespace Luau_Other {
        const uintptr_t LuaT_typenames                   = REBASE(0x67DCAB0);  // ✓ DATA
        const uintptr_t LuaT_eventname                   = REBASE(0x67DCB20);  // ✓ DATA
        const uintptr_t luaC_init                        = REBASE(0x26E0370);  // ✓ VALID
        const uintptr_t luaG_runerror                    = REBASE(0x26B7390);  // ✓ VALID
        const uintptr_t luaO_pushfstring                 = REBASE(0x2690140);  // ✓ VALID
        const uintptr_t luaM_visitgco                    = REBASE(0x26DFF30);  // ✓ VALID
        const uintptr_t luaF_Freeproto                   = REBASE(0x26B81A0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_assert                      = REBASE(0x26DBC90);  // ✓ VALID
        const uintptr_t luaB_print                       = REBASE(0x26D6FD0);  // ✓ DATA
        const uintptr_t luaB_error                       = REBASE(0x26D7430);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_gcinfo                      = REBASE(0x26DA5E0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_getfenv                     = REBASE(0x26D89E0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_getmetatable                = REBASE(0x26D7E60);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_next                        = REBASE(0x26DB1E0);  // ✓ VALID
        const uintptr_t luaB_newproxy                    = REBASE(0x26DC880);  // ✓ VALID
        const uintptr_t luaB_rawequal                    = REBASE(0x26D8CC0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_rawget                      = REBASE(0x26D8DD0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_rawset                      = REBASE(0x26D9860);  // ✓ DATA
        const uintptr_t luaB_rawlen                      = REBASE(0x26DA540);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_select                      = REBASE(0x26DBD40);  // ✓ VALID
        const uintptr_t luaB_setfenv                     = REBASE(0x26D8AA0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_setmetatable                = REBASE(0x26D7FE0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_tonumber                    = REBASE(0x26D70A0);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_tostring                    = REBASE(0x26DC820);  // ✓ VALID
        const uintptr_t luaB_type                        = REBASE(0x26DA600);  // ⚠ NEEDS_WARM
        const uintptr_t luaB_typeof                      = REBASE(0x26DAC00);  // ⚠ NEEDS_WARM
        const uintptr_t lua_checkstack                   = REBASE(0x268C3F0);  // ✓ VALID (использован для struct extraction)
        const uintptr_t pseudo2addr                      = REBASE(0x268C250);  // ✓ VALID
        const uintptr_t luaD_growstack                   = REBASE(0x268C4C0);  // ★ NEW (callback из lua_checkstack)
        const uintptr_t luaM_free                        = REBASE(0x26DFAD0);  // ✓ VALID
        const uintptr_t luaM_freegco                     = REBASE(0x26DFB80);  // ✓ VALID
        const uintptr_t luaM_freeclasspage               = REBASE(0x26E0040);  // ✓ VALID
        const uintptr_t lua_clock                        = REBASE(0x26E0C10);  // ✓ VALID
        const uintptr_t GcStep                           = REBASE(0x26B0960);  // ✓ VALID
        const uintptr_t luaM_toobig                      = REBASE(0x26DF9F0);  // ✓ VALID
        const uintptr_t luaL_argerrorL                   = REBASE(0x2698DA0);  // ✓ VALID
        const uintptr_t luaF_newproto                    = REBASE(0x26B7AD0);  // ✓ VALID
        const uintptr_t luaD_rawrunprotected             = REBASE(0x2691EE0);  // ✓ VALID
        const uintptr_t currfuncname                     = REBASE(0x514D160);  // ⚠ NEEDS_WARM
        const uintptr_t luaO_pushvfstring                = REBASE(0x26B5D00);  // ✓ VALID
        const uintptr_t luaA_toobject                    = REBASE(0x268C310);  // ✓ VALID
        const uintptr_t NewUserdataTagged                = REBASE(0x2690150);  // ✓ VALID
        const uintptr_t GetTypeName                      = REBASE(0x268CF50);  // ⚠ (mid-function, искать правильный старт)
        const uintptr_t GetObjectTypeName                = REBASE(0x26B93D0);  // ✓ VALID
        const uintptr_t GetObjectTypeNameString          = REBASE(0x26B9240);  // ✓ VALID
        const uintptr_t CallInternal                     = REBASE(0x268DB80);  // ✓ VALID (использован для struct extraction)
        const uintptr_t CallYieldable                    = REBASE(0x2691FF0);  // ✓ DATA (байты живые)
    };

    namespace Coroutine {
        const uintptr_t create                           = REBASE(0x26EBC70);  // ✓ VALID
        const uintptr_t running                          = REBASE(0x59EB070);  // ✓ VALID
        const uintptr_t status                           = REBASE(0x59E8DF0);  // ⚠ NEEDS_WARM
        const uintptr_t wrap                             = REBASE(0x59EADA0);  // ✓ VALID
        const uintptr_t yield                            = REBASE(0x59EB010);  // ✓ VALID
        const uintptr_t isyieldable                      = REBASE(0x59EB0E0);  // ✓ VALID
        const uintptr_t close                            = REBASE(0x59EB170);  // ✓ VALID
    };

    namespace Signal {
        const uintptr_t Disconnect                       = REBASE(0x422A100);  // ✓ VALID
        const uintptr_t ConnectionDisconnectRaw          = REBASE(0x4A9E0B0);  // ✓ VALID
        const uintptr_t ConnectionUnlink                 = REBASE(0x4A9E4F0);  // ✓ VALID
        const uintptr_t ConnectionConnected              = REBASE(0x4A9E240);  // ✓ VALID
        const uintptr_t ConnectionPushFront              = REBASE(0x4A9E740);  // ✓ VALID
        const uintptr_t RaiseEventInvocation             = REBASE(0x1D59AA0);  // ✓ VALID
        const uintptr_t GetArguments                     = REBASE(0x42CD100);  // ⚠ NEEDS_WARM
        const uintptr_t Once                             = REBASE(0x4228FC0);  // ✓ VALID
        const uintptr_t Wait                             = REBASE(0x4229160);  // ✓ VALID
    };

    namespace InstanceBridge {
        const uintptr_t Index                            = REBASE(0x4244A80);  // ✓ VALID (валидирован через "Instance.__index")
        const uintptr_t UserdataNamecall                 = REBASE(0x42461B0);  // ✓ VALID
        const uintptr_t NewIndex                         = REBASE(0x4242440);  // ✓ VALID
        // ★ NEW: identity-threshold globals для каждого метаметода
        const uintptr_t IdentityThreshold_NewIndex       = REBASE(0x8F42E10);  // ★ cs:dword в прологе NewIndex
        const uintptr_t IdentityThreshold_Namecall       = REBASE(0x8F42DE0);  // ★ cs:dword в прологе Namecall
    };

    namespace AppData {
        const uintptr_t Info                             = REBASE(0x1521490);  // ⚠ NEEDS_WARM
    };

    namespace Reflections {
        const uintptr_t TypeRegistration                 = REBASE(0x1A82EDF);  // ⚠ NEEDS_WARM
    };

    namespace Input {
        const uintptr_t FireMouseClick                   = REBASE(0x3C7E520);  // ✓ VALID (после Studio warmup)
        const uintptr_t FireRightMouseClick              = REBASE(0x3C7E6C0);  // ✓ VALID
        const uintptr_t FireProximityPrompt              = REBASE(0x312C010);  // ✓ VALID
        const uintptr_t FireMouseHover                   = REBASE(0x3C7FB10);  // ✓ VALID
        const uintptr_t FireMouseHoverLeave              = REBASE(0x3C7FCB0);  // ✓ VALID
    };

    namespace Crash {
        const uintptr_t LockViolationScriptCrash         = REBASE(0x8A21A30);  // ⚠ (не трогай вообще)
        const uintptr_t LockViolationInstanceCrash       = REBASE(0x8ACF1D8);  // ⚠
        const uintptr_t LockViolationInstanceCrashStudio = REBASE(0x8ACF1F0);  // ⚠
        const uintptr_t RBXCrashPtr                      = REBASE(0x8E1B188);  // ✓ DATA
    };

    namespace SharedString {
        const uintptr_t Create                           = REBASE(0x4AA8D10);  // ✓ VALID
        const uintptr_t Release                          = REBASE(0x824510);   // ✓ VALID
    };

    namespace RobloxProperty {
        const uintptr_t InternPropertyName               = REBASE(0x2AB03C0);  // ✓ VALID
        const uintptr_t LookupPropertyName               = REBASE(0x2AB07E0);  // ✓ VALID
        const uintptr_t GetProperty                      = REBASE(0x1D44010);  // ✓ VALID
    };

    namespace Scheduler {
        const uintptr_t StepWaitingHybridScripts         = REBASE(0x4335AA0);  // ✓ VALID
    };

    namespace Property {
        const uintptr_t ValueGetUnavailable              = REBASE(0xAC63D0);   // ✓ VALID
        const uintptr_t ValueSetUnavailable              = REBASE(0x7F7160);   // ✓ VALID
    };

    // ★ NEW: opcode dispatch tables (из Luau_Execute_Interpreter)
    namespace Opcodes {
        const uintptr_t RemapTable       = REBASE(0x26D6DE4);  // uint8_t[256] (bytecode-2) → canonical
        const uintptr_t JumpTable        = REBASE(0x26D6C68);  // uint32_t[95] canonical → handler_RVA
        constexpr size_t CanonicalCount  = 94;                  // 0..93 валидны, 94 = default
        // Dispatch logic:
        //   bytecode_byte -> (byte - 2) -> remap -> canonical -> jump -> handler
        //   real_opcode_byte = encoded_byte + 2
        constexpr int    ByteShift       = 2;
    };
}

namespace Aliases {
    inline auto GetLuaState = Offsets::GetGlobalState;
    inline auto LuaVM_Load  = Offsets::Luau::LoadModule;
    inline auto Luau_Execute = Offsets::Luau::Luau_Execute_Dispatcher;
}
