#include <iostream>
#include <cstdlib>
#include <fstream>
#include <exception>
#include <vector>
#include "IRInterpreter.hpp"
#include "IRGenerator.hpp"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "[ERROR] No program provided !\n";
        std::cerr << "[ERROR] Usage : ./bici your_program.bf\n";
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

    IRInterpreter irInterpreter;
    IRGenerator irGenerator;

    try {
        std::vector<IRInstruction> irProgram = irGenerator.GenerateIRFromRawInsts(programBuffer);
        irInterpreter.LoadIR(irProgram);
        irInterpreter.Interpret();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
