#include "Span.hpp"
#include <limits>

Span::Span() : _N(0), _numbers() {}

Span::Span(const Span& other) {
    *this = other;
}

Span& Span::operator=(const Span& other) {
    if (this != &other) {
        _N = other._N;
        _numbers = other._numbers;
    }
    return *this;
}

Span::~Span() {}

Span::Span(unsigned int N) : _N(N), _numbers() {}

void Span::addNumber(int number) {
    if (_numbers.size() >= _N)
        throw std::out_of_range("Span is full");
    _numbers.push_back(number);
}

int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers to find a span");
    std::vector<int> sortedNumbers = _numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    int minSpan = std::numeric_limits<int>::max();
    for (size_t i = 1; i < sortedNumbers.size(); ++i) {
        int span = sortedNumbers[i] - sortedNumbers[i - 1];
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}

int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::out_of_range("Not enough numbers to find a span");
    std::vector<int> sortedNumbers = _numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    return sortedNumbers.back() - sortedNumbers.front();
}

void Span::addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    if (std::distance(begin, end) + _numbers.size() > _N)
        throw std::out_of_range("Adding this range would exceed the span's capacity");
    _numbers.insert(_numbers.end(), begin, end);
}
