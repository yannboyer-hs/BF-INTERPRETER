#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

class Lexer {
    public:
        Lexer();

        void Fill(const std::string& code);
        char Next();
    private:
        bool IsValidBFInstruction(char pInst);

        std::size_t m_codePos;
        std::size_t m_codeLen;
        std::vector<char> m_code;
};

#endif