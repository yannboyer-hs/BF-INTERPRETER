#ifndef IRGENERATOR_HPP
#define IRGENERATOR_HPP

#include <optional>
#include <vector>
#include <cstdint>
#include "Lexer.hpp"

enum class IRInstKind {
    INCREMENT_POINTER = '>',
    DECREMENT_POINTER = '<',
    INCREMENT_BYTE = '+',
    DECREMENT_BYTE = '-',
    PRINT_BYTE = '.',
    READ_BYTE_STDIN = ',',
    JUMP_IF_ZERO = '[',
    JUMP_IF_NOT_ZERO = ']'
};

struct IRInst {
    IRInstKind kind;
    std::optional<uint8_t> operand;
};

class IRGenerator {
    public:
        IRGenerator() = default;

        std::vector<IRInst> GenerateIRFromRawInsts(const std::string& code);
    private:
        Lexer m_lexer;
};

#endif
