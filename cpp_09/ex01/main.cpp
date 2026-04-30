#include "RPN.hpp"
#include <exception>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    try {
        RPN claculator;
        claculator.calculate(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Error" << std::endl;
        return 1;
    }
        return 0;
}