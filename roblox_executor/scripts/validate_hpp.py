"""
validate_hpp.py — валидация offset'ов из Internal_Offsets.hpp против IDA базы.

Запуск: в IDA → File → Script file → выбрать этот файл.
Требует: rebase to 0 перед запуском.

Выдаёт: VALID / MID / ZEROS / NO_FUNC / DATA_OK / SUSPICIOUS для каждого offset'а.
"""
import re
import idc
import ida_funcs
import ida_bytes
import ida_name

HPP_PATH = r"C:\Users\Zumhad\Desktop\d\Internal_Offsets.hpp"  # поменяй под свой путь

pattern = re.compile(r"(\w+)\s*=\s*REBASE\(0x([0-9A-Fa-f]+)\)")

entries = []
with open(HPP_PATH, "r", encoding="utf-8", errors="ignore") as f:
    for line in f:
        m = pattern.search(line)
        if m:
            entries.append((m.group(1), int(m.group(2), 16)))

print(f"loaded {len(entries)} offsets\n")
print(f"{'NAME':38} {'ADDR':>12}  {'STATUS':20}  BYTES")
print("-" * 100)

stats = {"VALID": 0, "MID": 0, "ZEROS": 0, "NO_FUNC": 0, "DATA_OK": 0}

PROLOGUE_FIRSTS = {
    0x40, 0x41, 0x48, 0x49, 0x4C, 0x4D,   # REX prefixes
    0x53, 0x55, 0x56, 0x57,                # push rbx/rbp/rsi/rdi
    0xE9, 0xEB,                            # jmp (thunks)
    0xFF,                                  # indirect jmp
}

for name, rva in entries:
    first = ida_bytes.get_bytes(rva, 16)
    if not first or first == b"\x00" * 16:
        print(f"{name:38} {rva:>12x}  ZEROS                 cold/missing")
        stats["ZEROS"] += 1
        continue
    hex_bytes = first[:8].hex()
    func = ida_funcs.get_func(rva)
    if func is None:
        if first[0] != 0 or first[-1] != 0:
            print(f"{name:38} {rva:>12x}  DATA_OK               {hex_bytes}")
            stats["DATA_OK"] += 1
        else:
            print(f"{name:38} {rva:>12x}  NO_FUNC               {hex_bytes}")
            stats["NO_FUNC"] += 1
        continue
    if func.start_ea != rva:
        print(f"{name:38} {rva:>12x}  MID_FUNC (start {func.start_ea:x})")
        stats["MID"] += 1
        continue
    if first[0] in PROLOGUE_FIRSTS:
        print(f"{name:38} {rva:>12x}  VALID                 {hex_bytes}")
        stats["VALID"] += 1
    else:
        print(f"{name:38} {rva:>12x}  SUSPICIOUS            {hex_bytes}")
        stats["MID"] += 1

print("\n" + "=" * 100)
print(f"SUMMARY: " + "  ".join(f"{k}={v}" for k, v in stats.items()))
