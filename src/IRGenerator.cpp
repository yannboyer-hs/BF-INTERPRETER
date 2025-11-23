#include "IRGenerator.hpp"

std::vector<IRInst> IRGenerator::GenerateIRFromRawInsts(const std::string& code) {
    m_lexer.Fill(code);

    char c = m_lexer.Next();

    std::vector<IRInst> tmpPrg;

    while (c) {
        IRInst irInst;
        switch (c) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
                {
                    uint8_t iCombo = 1; // We already have one occurence of the instruction.
                    char s = m_lexer.Next();

                    while (c == s) {
                        iCombo++;
                        s = m_lexer.Next();
                    }

                    irInst = { static_cast<IRInstKind>(c), iCombo };

                    c = s;
                }
                break;
            case ',':
            case '[':
            case ']':
                irInst = { static_cast<IRInstKind>(c), {} };
                c = m_lexer.Next();
                break;
            default: continue;
        }

        tmpPrg.push_back(irInst);
    }

    return tmpPrg;
}