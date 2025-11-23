#include "IRInterpreter.hpp"
#include <memory>
#include <format>
#include <iostream>
#include <stdexcept>

IRInterpreter::IRInterpreter() {
    m_memoryPtr = 0;
    m_instPtr = 0;
    m_memory.fill(0);
}

void IRInterpreter::LoadIR(const std::vector<IRInst> prg) {
    m_program = prg;
}

void IRInterpreter::InterpretIR() {
    std::size_t programLen = m_program.size();
    std::vector<uint64_t> stack;
    // I'm dumb, please kill me...
    std::unique_ptr<uint64_t[]> targets = std::make_unique<uint64_t[]>(programLen);

    // Precomputing jumps ahead of time.
    for (std::size_t i = 0, j; i < programLen; i++) {
        if (m_program[i].kind == IRInstKind::JUMP_IF_ZERO) stack.push_back(i);
        else if (m_program[i].kind == IRInstKind::JUMP_IF_NOT_ZERO) {
            if (stack.empty()) {
                throw std::runtime_error(std::format("[ERROR] Unmatched ']' at {}", i + 1));
            } else {
                j = stack.back();
                stack.pop_back();
                targets[i] = j;
                targets[j] = i;
            }
        }
    }

    while (m_instPtr < programLen) {
        IRInst irInst = m_program[m_instPtr];

        switch (irInst.kind) {
            case IRInstKind::INCREMENT_POINTER: m_memoryPtr += irInst.operand.value(); break;
            case IRInstKind::DECREMENT_POINTER: m_memoryPtr -= irInst.operand.value(); break;
            case IRInstKind::INCREMENT_BYTE: m_memory[m_memoryPtr] += irInst.operand.value(); break;
            case IRInstKind::DECREMENT_BYTE: m_memory[m_memoryPtr] -= irInst.operand.value(); break;
            case IRInstKind::PRINT_BYTE:
                {
                    uint8_t repeatCount = irInst.operand.value();
                    char byteToPrintAsChar = static_cast<char>(m_memory[m_memoryPtr]);

                    for (uint8_t i = 0; i < repeatCount; i++) {
                        std::cout << byteToPrintAsChar;
                        std::cout.flush();
                    }
                }
                break;
            case IRInstKind::READ_BYTE_STDIN:
                {
                    char inputByte;
                    std::cin >> inputByte;
                    std::cin.clear();
                    m_memory[m_memoryPtr] = static_cast<uint8_t>(inputByte);
                }
                break;
            case IRInstKind::JUMP_IF_ZERO:
                if (m_memory[m_memoryPtr] == 0)
                    m_instPtr = targets[m_instPtr];
                break;
            case IRInstKind::JUMP_IF_NOT_ZERO:
                if (m_memory[m_memoryPtr] != 0)
                    m_instPtr = targets[m_instPtr];
                break;
        }

        m_instPtr++;
    }
}