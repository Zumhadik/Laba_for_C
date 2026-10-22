# Luau Opcode Mapping — version-117ad38284844374

## Как устроена opcode-система

Luau_Execute_Interpreter начинается с dispatch loop'а:

```asm
loc_26CA390:
    add     rax, 0FFFFFFFFFFFFFFFEh         ; opcode - 2 (нормализация)
    cmp     rax, 0FDh                        ; <= 253?
    ja      default_handler
    movzx   eax, ds:byte_26D6DE4[r9+rax]    ; remap table → canonical
    mov     ecx, ds:jpt_26CA3B4[r9+rax*4]   ; jump table → handler RVA
    add     rcx, r9                          ; + ImageBase
    jmp     rcx
```

## Таблицы

- **`0x26D6DE4`** — `uint8_t remap_table[256]`.
  Mapping: encoded_opcode_byte → canonical_index.
- **`jpt_26CA3B4`** (реальный адрес в `.rdata`) — `uint32_t jump_table[~95]`.
  Mapping: canonical_index → handler RVA.
- **Canonical 94** — "invalid/default" handler (общий для всех неиспользуемых байт).

## Encoded opcodes used (из remap table)

**94 distinct opcodes** в этой версии. Encoded bytes:

```
0x00 0x05 0x06 0x08 0x0C 0x0F 0x11 0x13 0x14 0x18 0x19 0x21 0x22 0x25
0x26 0x29 0x2A 0x2B 0x2E 0x2F 0x32 0x35 0x3D 0x40 0x41 0x42 0x43 0x48
0x49 0x4C 0x4D 0x4E 0x50 0x54 0x55 0x56 0x57 0x59 0x5F 0x61 0x62 0x63
0x64 0x66 0x67 0x69 0x6C 0x71 0x77 0x83 0x8B 0x8D 0x8E 0x91 0x92 0x95
0x98 0x9B 0x9D 0x9E 0xA0 0xA6 0xAA 0xAC 0xAF 0xB1 0xB4 0xB5 0xB6 0xB8
0xBA 0xBC 0xBE 0xBF 0xC6 0xC7 0xCD 0xD3 0xD5 0xD8 0xDD 0xDE 0xDF 0xE0
0xE5 0xE6 0xE7 0xE9 0xEA 0xEB 0xF5 0xF6 0xF8 0xFD
```

## Как определить какой encoded byte = какой `OP_*`

Нет прямого способа — нужно сопоставить handler'ы с эталонным luau. Два подхода:

1. **Pattern-match handler'ов.** Для каждого canonical index смотрим что делает handler
   (chars/code pattern) и сравниваем с reference luau_execute.cpp из [luau github](https://github.com/luau-lang/luau).
   Например:
   - handler который делает `settableaux(k[Bx])` → `OP_SETGLOBAL`
   - handler который делает `L->ci->top = top+C-1; return` → `OP_RETURN`
   - handler который `pc = pc + sBx` без условия → `OP_JUMP`

2. **Bootstrap через fixed opcodes.** `OP_NOP` в luau = canonical index 0, часто остаётся
   без ремаппинга. У тебя `0x00 → canonical 0` — вероятно это `OP_NOP`.
   Дальше по частотности в compiled bytecode (OP_LOADNIL, OP_RETURN самые частые)
   находишь остальные.

## Что делать с этой информацией

Для твоего компилятора:

```cpp
// В тебе собственный luau-compiler fork который эмитит стандартные OP_* bytes.
// Проходишь bytecode postprocess'ом и REMAP'ишь canonical → encoded:

uint8_t canonical_to_encoded[256];
for (int enc = 0; enc < 256; ++enc) {
    uint8_t canon = remap_table[enc];
    canonical_to_encoded[canon] = enc;  // inverse mapping
}

// Теперь в твоём bytecode'е каждый opcode byte переписываешь:
for (size_t i = 0; i < bytecode_size; i += instruction_size(...)) {
    uint8_t canon_op = bytecode[i];
    bytecode[i] = canonical_to_encoded[canon_op];
}
```

После этого bytecode готов к `Luau_Load`.

## Jump table resolution

Script `dump_opcodes.py` не сработает если IDA не разобрала switch как jump table.
Чини вручную:

1. `G → 26CA390` (loc_26CA390 внутри Luau_Execute_Interpreter)
2. На инструкции `mov ecx, ds:jpt_26CA3B4[r9+rax*4]` → двойной клик по `jpt_26CA3B4`
3. IDA перейдёт на реальный адрес table — скорее всего в `.rdata`
4. Запиши этот адрес и подставь в `dump_opcodes.py` как `JPT_LABEL` или прямо как RVA
