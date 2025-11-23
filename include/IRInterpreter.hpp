#ifndef IRINTERPRETER_HPP
#define IRINTERPRETER_HPP

#include <vector>
#include <array>
#include "IRGenerator.hpp"

class IRInterpreter {
    public:
        IRInterpreter();

        void LoadIR(const std::vector<IRInst> prg);
        void InterpretIR();
    private:
        static constexpr uint32_t MEMORY_CELLS_COUNT = 100000; // Not ideal...
        uint64_t m_memoryPtr;
        uint64_t m_instPtr;
        std::array<uint8_t, MEMORY_CELLS_COUNT> m_memory;
        std::vector<IRInst> m_program;
};

#endif
