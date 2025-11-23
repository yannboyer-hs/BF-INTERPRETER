#include "Lexer.hpp"

Lexer::Lexer() {
    m_codePos = 0;
    m_codeLen = 0;
    m_code.resize(0);
}

void Lexer::Fill(const std::string& code) {
    for (char c : code) {
        m_code.push_back(c);
    }

    m_codeLen = m_code.size();
}

bool Lexer::IsValidBFInstruction(char pInst) {
    const std::string VALID_INSTS = "><+-.,[]";
    if (VALID_INSTS.find(pInst) != std::string::npos) return true;
    else return false;
}

char Lexer::Next() {
    while (m_codePos < m_codeLen && !IsValidBFInstruction(m_code[m_codePos]))
        m_codePos++;
    
    if (m_codePos >= m_codeLen) return 0;
    return m_code[m_codePos++];
}