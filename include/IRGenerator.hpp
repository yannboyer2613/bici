#ifndef IR_GENERATOR_HPP
#define IR_GENERATOR_HPP

#include "IR.hpp"
#include <vector>
#include <string>
#include "Lexer.hpp"

class IRGenerator {
    public:
        IRGenerator() = default;

        std::vector<IRInstruction> GenerateIRFromRawInsts(std::string& code);
    private:
        Lexer m_lexer;
};

#endif
