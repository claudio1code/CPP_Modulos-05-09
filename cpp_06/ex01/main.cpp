#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    // 1. Criar e preencher a nossa estrutura
    Data cadete;
    cadete.id = 42;
    cadete.name = "Claudio";
    cadete.level = 8.5f;

    std::cout << "--- ORIGINAL ---" << std::endl;
    // Imprime o endereço real da variável na RAM
    std::cout << "Memory address: " << &cadete << std::endl;
    std::cout << "ID: " << cadete.id << " | Name: " << cadete.name << " | Level: " << cadete.level << std::endl;

    // 2. Serializar (O reinterpret_cast entra em ação!)
    uintptr_t raw = Serializer::serialize(&cadete);

    std::cout << "\n--- AFTER SERIALIZATION ---" << std::endl;
    std::cout << "Valor raw (uintptr_t): " << raw << std::endl;
    std::cout << "(This is the memory address saved as a mathematical number)" << std::endl;

    // 3. Deserializar (Recuperar o ponteiro a partir do número)
    Data* recuperado = Serializer::deserialize(raw);

    std::cout << "\n--- RECOVERED STATE ---" << std::endl;
    std::cout << "Recovered address: " << recuperado << std::endl;
    std::cout << "ID: " << recuperado->id << " | Nome: " << recuperado->name << " | Level: " << recuperado->level << std::endl;

    // 4. A prova final exigida pelo PDF
    std::cout << "\n--- CONCLUSION ---" << std::endl;
    if (&cadete == recuperado) {
        std::cout << "SUCCESS! The pointers are exactly the same and the memory is intact." << std::endl;
    } else {
        std::cout << "FAILURE! The pointers are different." << std::endl;
    }

    return 0;
}