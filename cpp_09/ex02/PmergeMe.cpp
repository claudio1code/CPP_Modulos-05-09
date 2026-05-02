#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _vector(), _deque() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        // Proteção 1: Argumentos vazios (ex: "")
        if (arg.empty()) {
            throw std::runtime_error("Error: empty argument");
        }
        
        // Proteção 2: Letras e lixo (apenas aceita dígitos e sinal de +)
        for (size_t j = 0; j < arg.length(); ++j) {
            if (!std::isdigit(arg[j]) && !(j == 0 && arg[j] == '+')) {
                throw std::runtime_error("Error: invalid character");
            }
        }

        // Proteção 3: Limites seguros usando strtol
        long number = std::strtol(arg.c_str(), NULL, 10);
        
        // PDF exige números positivos
        if (number < 0 || number > 2147483647) {
            throw std::runtime_error("Error: number out of range");
        }
        
        // FINALMENTE: Guardar os números nos dois contentores!
        _vector.push_back(static_cast<int>(number));
        _deque.push_back(static_cast<int>(number));
    }
}

void PmergeMe::execute() {
// 1. Imprimir a sequência antes da ordenação
    printSequence("Before: ", _vector);

    // 2. Medir tempo e ordenar o std::vector
    struct timeval start_vec, end_vec;
    gettimeofday(&start_vec, NULL);
    
    fordJohnsonSort(_vector); // Chamada do motor de ordenação
    
    gettimeofday(&end_vec, NULL);
    // Calcular a diferença em microssegundos
    long time_vec = (end_vec.tv_sec - start_vec.tv_sec) * 1000000L + (end_vec.tv_usec - start_vec.tv_usec);

    // 3. Medir tempo e ordenar o std::deque
    struct timeval start_deq, end_deq;
    gettimeofday(&start_deq, NULL);
    
    fordJohnsonSort(_deque); // Chamada do motor de ordenação
    
    gettimeofday(&end_deq, NULL);
    long time_deq = (end_deq.tv_sec - start_deq.tv_sec) * 1000000L + (end_deq.tv_usec - start_deq.tv_usec);

    // 4. Imprimir a sequência depois da ordenação
    // Podemos imprimir o _vector porque o resultado final tem de ser igual em ambos
    printSequence("After:  ", _vector);

    // 5. Imprimir as linhas de tempo finais conforme exigido pelo PDF
    std::cout << "Time to process a range of " << _vector.size() 
              << " elements with std::vector : " << time_vec << " us" << std::endl;
              
    std::cout << "Time to process a range of " << _deque.size() 
              << " elements with std::deque  : " << time_deq << " us" << std::endl;
}

void PmergeMe::printSequence(const std::string& message, const std::vector<int>& seq) const {

    std::cout << message;
    
    // Se a sequência for gigante, convém limitar a impressão a 5 ou 10 números
    // para não encher o terminal do avaliador.
    size_t limit = (seq.size() > 5) ? 5 : seq.size();
    
    for (size_t i = 0; i < limit; ++i) {
        std::cout << seq[i] << " ";
    }
    
    if (seq.size() > 5) {
        std::cout << "[...]";
    }
    std::cout << std::endl;
}


// Fórmula: J(n) = J(n-1) + 2 * J(n-2)
int PmergeMe::getJacobsthalNumber(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int a = 0;
    int b = 1;
    int next = 0;
    
    for (int i = 2; i <= n; ++i) {
        next = b + 2 * a;
        a = b;
        b = next;
    }
    return next;
}
