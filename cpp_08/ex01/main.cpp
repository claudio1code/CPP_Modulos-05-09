#include "Span.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

int main() {
    std::cout << "--- Basic Test ---" << std::endl;
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest: " << sp.shortestSpan() << " (Expected: 2)" << std::endl;
        std::cout << "Longest: " << sp.longestSpan() << " (Expected: 14)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\n--- Full Span Exception Test ---" << std::endl;
    try {
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        std::cout << "Adding third number to capacity 2..." << std::endl;
        sp.addNumber(3);
    } catch (const std::exception& e) {
        std::cerr << "Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n--- Empty/Single Element Exception Test ---" << std::endl;
    try {
        Span sp(5);
        sp.addNumber(42);
        std::cout << "Calculating span with only 1 number..." << std::endl;
        sp.shortestSpan();
    } catch (const std::exception& e) {
        std::cerr << "Caught expected error: " << e.what() << std::endl;
    }

    std::cout << "\n--- Large Scale Test (10.000 numbers) ---" << std::endl;
    try {
        unsigned int size = 10000;
        Span bigSpan(size);
        std::vector<int> bigVector;

        std::srand(std::time(0));
        for (unsigned int i = 0; i < size; i++) {
            bigVector.push_back(std::rand());
        }

        bigSpan.addRange(bigVector.begin(), bigVector.end());
        std::cout << "Big Span size: " << size << std::endl;
        std::cout << "Shortest Span: " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << bigSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
