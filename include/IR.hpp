#ifndef IR_HPP
#define IR_HPP

#include <optional>
#include <cstdint>

enum class IRInstructionKind {
    IncrementPointer = '>',
    DecrementPointer = '<',
    IncrementByte = '+',
    DecrementByte = '-',
    PrintByte = '.',
    ReadByte = ',',
    JumpIfZero = '[',
    JumpIfNotZero = ']',
};

struct IRInstruction {
    IRInstructionKind kind;
    std::optional<uint8_t> operand;
};

#endif
