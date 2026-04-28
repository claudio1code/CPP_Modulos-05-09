#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <string>
#include <vector>
#include <algorithm>
#include <exception>

class Span {
    private:
        unsigned int         _N;
        std::vector<int>     _numbers;
    public:
        Span();
        Span(const Span& other);
        Span& operator=(const Span& other);
        ~Span();

        Span(unsigned int N);
        void addNumber(int number);
        int shortestSpan() const;
        int longestSpan() const;
        void addRange(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};

#endif
