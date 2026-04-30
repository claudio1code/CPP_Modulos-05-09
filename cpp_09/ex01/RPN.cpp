#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {
    *this = other;
}

RPN& RPN::operator=(const RPN& other) {
    (void)other;
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::performOperation(const char& op, int a, int b) const {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw std::runtime_error("Error");
        return a / b;
    }
    return 0;
}

void RPN::calculate(const std::string& expression) {
    std::stack<int> stack;
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (c  == ' ') {
            continue;
        }
        if (std::isdigit(c)) {
            stack.push(c - '0');
        }
        else if (isOperator(c)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Error");
            }
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();
            int result = performOperation(c, a, b);
            stack.push(result);
        } else {
            throw std::runtime_error("Error");
        }
    }
        if (stack.size() != 1)
            throw std::runtime_error("Error");
        std::cout << stack.top() << std::endl;
}
