#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>
# include <stdexcept>

class RPN {
    private:
        bool isOperator(const char token) const;
        int performOperation(const char& op, int a, int b) const;
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();
        void calculate(const std::string& expression);
};

#endif
