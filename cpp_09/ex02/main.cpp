#include "PmergeMe.hpp"
#include <iostream>
#include <exception>

int main(int argc, char **argv) {
    // 1. O programa precisa de pelo menos 1 argumento (além do nome do programa)
    if (argc < 2) {
        std::cerr << "Error: no arguments provided." << std::endl;
        return 1;
    }

    try {
        // 2. Instanciar a máquina
        PmergeMe sorter;

        // 3. Alimentar a máquina (valida e guarda nos contentores)
        sorter.parseInput(argc, argv);

        // 4. Executar a ordenação e medição de tempo
        sorter.execute();

    } 
    catch (const std::exception& e) {
        // 5. Se qualquer throw for atirado no parseInput (letras, overflow, etc),
        // o programa salta direto para aqui e imprime o erro no STDERR.
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0; // Sucesso absoluto!
}