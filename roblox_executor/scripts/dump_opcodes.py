"""
dump_opcodes.py — выдёргивает Luau opcode mapping из распакованного дампа Roblox.

Что находим:
  1. remap_table (uint8_t[256]) — маппит encoded opcode byte на canonical index
  2. jump_table (RVA[~94])     — RVA handler'а для каждого canonical index

Запуск: в IDA → File → Script file.
Требует: rebase to 0, Luau_Execute_Interpreter должен быть определён.
"""
import idc
import ida_name
import ida_bytes

# адреса из Luau_Execute_Interpreter (version-117ad38284844374)
REMAP_RVA = 0x26D6DE4

# IDA-label для jump table — ВНИМАНИЕ: это label на инструкцию `jmp rcx`,
# а не на сам table. Реальный table в .rdata, резолвим через name lookup.
JPT_LABEL = "jpt_26CA3B4"

# Количество canonical opcode'ов (из `cmp rax, 0FDh` + nop byte = 253)
CANONICAL_COUNT = 94  # индекс 94 используется как "invalid/default"

# ----------------------------------------------------------------------------
# Resolve real jump table address
# ----------------------------------------------------------------------------
jpt_addr = ida_name.get_name_ea(idc.BADADDR, JPT_LABEL)
if jpt_addr == idc.BADADDR:
    print(f"[!] Could not find {JPT_LABEL} — IDA ещё не разобрала switch")
    print(f"[!] Найди вручную: открой Luau_Execute_Interpreter, кликни на")
    print(f"    инструкцию `mov ecx, ds:jpt_26CA3B4[r9+rax*4]`, перейди в")
    print(f"    operand → увидишь реальный адрес table")
    raise SystemExit(1)

print(f"jpt_{JPT_LABEL} at: 0x{jpt_addr:X}")

# ----------------------------------------------------------------------------
# Read remap table (256 bytes)
# ----------------------------------------------------------------------------
remap = {}
for i in range(256):
    canonical = ida_bytes.get_byte(REMAP_RVA + i)
    remap[i] = canonical

# ----------------------------------------------------------------------------
# Read jump table (RVAs, 4 bytes each)
# ----------------------------------------------------------------------------
handlers = {}
for i in range(CANONICAL_COUNT + 1):
    rva = ida_bytes.get_dword(jpt_addr + i * 4)
    handlers[i] = rva

# ----------------------------------------------------------------------------
# Combine and print
# ----------------------------------------------------------------------------
print("\nencoded_byte  canonical_idx  handler_rva")
print("=" * 50)

used = {}
for enc in range(256):
    canon = remap[enc]
    if canon != 94 and canon < len(handlers):
        handler = handlers[canon]
        used[enc] = (canon, handler)
        print(f"  0x{enc:02X}         {canon:3d}         0x{handler:08X}")

print(f"\ntotal distinct encoded opcodes: {len(used)}")
print(f"canonical range: 0..{max(c for c, _ in used.values())}")

# ----------------------------------------------------------------------------
# Dump raw tables as JSON for use in your compiler
# ----------------------------------------------------------------------------
import json
output = {
    "remap_table": {f"0x{i:02X}": remap[i] for i in range(256)},
    "jump_table_rvas": {str(i): f"0x{handlers[i]:08X}" for i in range(CANONICAL_COUNT + 1)},
    "encoded_to_handler": {f"0x{e:02X}": {"canonical": c, "handler": f"0x{h:08X}"}
                           for e, (c, h) in used.items()}
}
out_path = r"C:\Users\Zumhad\Desktop\d\opcode_mapping.json"
with open(out_path, "w") as f:
    json.dump(output, f, indent=2)
print(f"\nsaved: {out_path}")
