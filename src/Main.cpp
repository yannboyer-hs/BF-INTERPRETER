#include <iostream>
#include <cstdlib>
#include <exception>
#include <fstream>
#include "IRGenerator.hpp"
#include "IRInterpreter.hpp"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "[ERROR] No program provided !\n";
        std::cerr << "[ERROR] Usage : ./BFInterpreter my_program.bf\n";
        return EXIT_FAILURE;
    }

    std::string programPath = std::string(argv[1]);

    std::ifstream programFile(programPath);

    if (!programFile.is_open()) {
        std::cerr << "[ERROR] Unable to open the file !\n";
        return EXIT_FAILURE;
    }

    char ch;
    std::string programBuffer;
    while (programFile.good()) {
        programFile.get(ch);
        programBuffer.push_back(ch);
    }

    programFile.close();

    IRGenerator irGenerator;
    IRInterpreter irInterpreter;

    std::vector<IRInst> program = irGenerator.GenerateIRFromRawInsts(programBuffer);
    irInterpreter.LoadIR(program);
    try {
        irInterpreter.InterpretIR();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}