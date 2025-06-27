#include "IRGenerator.hpp"
#include <stdexcept>

std::vector<IRInstruction> IRGenerator::GenerateIRFromRawInsts(std::string& code) {
    m_lexer.Fill(code);

    char c = m_lexer.Next();

    std::vector<IRInstruction> program;

    while (c) {
        IRInstruction irInst;
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
                {
                    char s = m_lexer.Next();
                    uint8_t streakCombo = 1; // We already have one occurence of the instruction.

                    while (c == s) {
                        if (streakCombo == 255)
                            throw std::runtime_error("[ERROR] Streak Combo optimization is limited to 255 occurence of the same instruction in a single combo !");
                        streakCombo++;
                        s = m_lexer.Next();
                    }

                    irInst = { static_cast<IRInstructionKind>(c), streakCombo };

                    c = s;
                }
                break;
            case ',':
            case '[':
            case ']':
                {
                    irInst = { static_cast<IRInstructionKind>(c), {} };
                    c = m_lexer.Next();
                }
                break;
            default: continue;
        }

        program.push_back(irInst);
    }

    return program;
}
