#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Erro: Número de argumentos inválido." << std::endl;
        std::cerr << "Uso: ./convert <valor_a_converter>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}