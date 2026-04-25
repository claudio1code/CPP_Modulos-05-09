#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    // 1. Criar e preencher a nossa estrutura
    Data cadete;
    cadete.id = 42;
    cadete.name = "Claudio";
    cadete.level = 8.5f;

    std::cout << "--- ESTADO ORIGINAL ---" << std::endl;
    // Imprime o endereço real da variável na RAM
    std::cout << "Endereço na memória: " << &cadete << std::endl;
    std::cout << "ID: " << cadete.id << " | Nome: " << cadete.name << " | Level: " << cadete.level << std::endl;

    // 2. Serializar (O reinterpret_cast entra em ação!)
    uintptr_t raw = Serializer::serialize(&cadete);

    std::cout << "\n--- APÓS SERIALIZAÇÃO ---" << std::endl;
    std::cout << "Valor raw (uintptr_t): " << raw << std::endl;
    std::cout << "(Isto é o endereço de memória guardado como um número matemático)" << std::endl;

    // 3. Deserializar (Recuperar o ponteiro a partir do número)
    Data* recuperado = Serializer::deserialize(raw);

    std::cout << "\n--- ESTADO RECUPERADO ---" << std::endl;
    std::cout << "Endereço recuperado: " << recuperado << std::endl;
    std::cout << "ID: " << recuperado->id << " | Nome: " << recuperado->name << " | Level: " << recuperado->level << std::endl;

    // 4. A prova final exigida pelo PDF
    std::cout << "\n--- CONCLUSÃO ---" << std::endl;
    if (&cadete == recuperado) {
        std::cout << "SUCESSO! Os ponteiros são exatamente iguais e a memória está intacta." << std::endl;
    } else {
        std::cout << "FALHA! Os ponteiros estão diferentes." << std::endl;
    }

    return 0;
}