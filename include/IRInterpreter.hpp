#ifndef IR_INTERPRETER_HPP
#define IR_INTERPRETER_HPP

#include <vector>
#include <array>
#include <cstdint>
#include "IR.hpp"

class IRInterpreter {
    public:
        IRInterpreter();

        void LoadIR(const std::vector<IRInstruction> irProgram);
        void Interpret();
    private:
        static constexpr uint32_t TOTAL_MEMORY_LEN = 100000;

        std::array<uint8_t, TOTAL_MEMORY_LEN> m_memory;

        uint64_t m_memoryPointer;
        uint64_t m_instructionPointer;

        std::vector<IRInstruction> m_program;
};

#endif
