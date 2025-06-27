#include "IRInterpreter.hpp"
#include <memory>
#include <format>
#include <iostream>

IRInterpreter::IRInterpreter() {
    m_memory.fill(0);
    m_memoryPointer = 0;
    m_instructionPointer = 0;
}

void IRInterpreter::LoadIR(const std::vector<IRInstruction> irProgram) {
    m_program = irProgram; // I genuinely don't think passing by reference would improve performance, it's only done once.
}

void IRInterpreter::Interpret() {
    std::size_t programLen = m_program.size();
    std::vector<uint64_t> stack;
    // Silly hack to make an array with a non constant size.
    std::unique_ptr<uint64_t[]> targets = std::make_unique<uint64_t[]>(programLen);

    // Precomputing Jumps...
    for (std::size_t i = 0, j; i < programLen; i++) {
        if (m_program[i].kind == IRInstructionKind::JumpIfZero) {
            stack.push_back(i);
        } else if (m_program[i].kind == IRInstructionKind::JumpIfNotZero) {
            if (stack.empty()) {
                throw std::runtime_error(std::format("[ERROR] Unmatched ']' at byte {}", i + 1));
            } else {
                j = stack.back();
                stack.pop_back();
                targets[i] = j;
                targets[j] = i;
            }
        }
    }

    // Do the interpretation of the Brainfuck program.
    while (m_instructionPointer < programLen) {
        IRInstruction irInst = m_program[m_instructionPointer];

        switch (irInst.kind) {
            case IRInstructionKind::IncrementPointer: m_memoryPointer += irInst.operand.value(); break;
            case IRInstructionKind::DecrementPointer: m_memoryPointer -= irInst.operand.value(); break;
            case IRInstructionKind::IncrementByte: m_memory[m_memoryPointer] += irInst.operand.value(); break;
            case IRInstructionKind::DecrementByte: m_memory[m_memoryPointer] -= irInst.operand.value(); break;
            case IRInstructionKind::PrintByte:
                {
                    uint8_t prnCount = irInst.operand.value();
                    char byteToPrintAsChar = static_cast<char>(m_memory[m_memoryPointer]);

                    for (uint8_t i = 0; i < prnCount; i++) {
                        std::cout << byteToPrintAsChar;
                        std::cout.flush();
                    }
                }
                break;
            case IRInstructionKind::ReadByte:
                {
                    char inputByte;
                    std::cin >> inputByte;
                    std::cin.clear();
                    m_memory[m_memoryPointer] = static_cast<uint8_t>(inputByte);
                }
                break;
            case IRInstructionKind::JumpIfZero:
                if (m_memory[m_memoryPointer] == 0)
                    m_instructionPointer = targets[m_instructionPointer];
                break;
            case IRInstructionKind::JumpIfNotZero:
                if (m_memory[m_memoryPointer] != 0) {
                    m_instructionPointer = targets[m_instructionPointer];
                }
                break;
        }

        m_instructionPointer++;
    }
}
