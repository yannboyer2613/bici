#include "Lexer.hpp"

Lexer::Lexer() {
    m_positionInCode = 0;
    m_code.resize(0);
}

void Lexer::Fill(const std::string& code) {
    for (auto c : code) {
        m_code.push_back(c);
    }
}

bool Lexer::IsValidBrainfuckInstruction(char instruction) {
    std::string validInsts = "><+-.,[]";
    if (validInsts.find(instruction) != std::string::npos)
        return true;
    else
        return false;
}

char Lexer::Next() {
    std::size_t codeLen = m_code.size();
    while (m_positionInCode < codeLen && !IsValidBrainfuckInstruction(m_code[m_positionInCode]))
        m_positionInCode++;

    if (m_positionInCode >= codeLen) return 0;
    return m_code[m_positionInCode++];
}
