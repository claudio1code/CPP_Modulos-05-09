#include "ScalarConverter.hpp"

enum eType {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    PSEUDO,
    IMPOSSIBLE
};

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
   (void)other;
    *this = other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
  (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

static eType getType(const std::string& literal) {
    if (literal == "nan" || literal == "+inf" || literal == "-inf" ||
        literal == "nanf" || literal == "+inff" || literal == "-inff") {
        return PSEUDO;
    }

    if (literal.length() == 1 && !std::isdigit(literal[0]) && std::isprint(literal[0])) {
        return CHAR;
    }

    int i = 0;
    int dots = 0;
    int length = literal.length();
    bool hasDigits = false;

    if (literal[i] == '-' || literal[i] == '+') i++;
    if (i == length) return IMPOSSIBLE;

    for (; i < length; i++) {
        if (literal[i] == '.') dots++;
        else if (literal[i] == 'f' && i == length - 1) {
            if (dots <= 1 && hasDigits) return FLOAT;
            return IMPOSSIBLE; 
        }
        else if (!std::isdigit(literal[i])) return IMPOSSIBLE; 
        else hasDigits = true;
    }

    if (dots > 1 || !hasDigits) return IMPOSSIBLE;
    if (dots == 1) return DOUBLE;                  
    return INT;                                    
}

void ScalarConverter::convert(const std::string& literal) {
    eType type = getType(literal);
    switch (type) {
        case CHAR:{
            char c = literal[0];
            int i = static_cast<int>(c);
            float f = static_cast<float>(c);
            double d = static_cast<double>(c);

            if (i >= 32 && i <= 126) {
                std::cout << "char: '" << c << "'" << std::endl;
            } else if (i >= 0 && i <= 255) {
                std::cout << "char: Non displayable" << std::endl;
            } else {
                std::cout << "char: impossible" << std::endl;
            } 
            std::cout << "int: " << i << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "float: " << f << std::endl;
            std::cout << "double: " << d << std::endl;
            break;
        }
        case INT:{
            int i = std::atoi(literal.c_str());
            char c = static_cast<char>(i);
            float f = static_cast<float>(i);
            double d = static_cast<double>(i);

            if (i >= 32 && i <= 126) {
                std::cout << "char: '" << c << "'" << std::endl;
            } else if (i >= 0 && i <= 255) {
                std::cout << "char: Non displayable" << std::endl;
            } else {
                std::cout << "char: impossible" << std::endl;
            }
            std::cout << "int: " << i << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "float: " << f << std::endl;
            std::cout << "double: " << d << std::endl;
            break;
        }
        case FLOAT:{
            float f = std::atof(literal.c_str());
            char c = static_cast<char>(f);
            int i = static_cast<int>(f);
            double d = static_cast<double>(f);

            if (i >= 32 && i <= 126) {
                std::cout << "char: '" << c << "'" << std::endl;
            } else if (i >= 0 && i <= 255) {
                std::cout << "char: Non displayable" << std::endl;
            } else {
                std::cout << "char: impossible" << std::endl;
            }
            std::cout << "int: " << i << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "float: " << f << std::endl;
            std::cout << "double: " << d << std::endl;
            break;
        }
        case DOUBLE:{
            double d = std::atof(literal.c_str());
            char c = static_cast<char>(d);
            int i = static_cast<int>(d);
            float f = static_cast<float>(d);

            if (i >= 32 && i <= 126) {
                std::cout << "char: '" << c << "'" << std::endl;
            } else if (i >= 0 && i <= 255) {
                std::cout << "char: Non displayable" << std::endl;
            } else {
                std::cout << "char: impossible" << std::endl;
            }
            std::cout << "int: " << i << std::endl;
            std::cout << std::fixed << std::setprecision(1);
            std::cout << "float: " << f << std::endl;
            std::cout << "double: " << d << std::endl;
            break;
        }
        case PSEUDO: {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            
            if (literal == "nan" || literal == "nanf") {
                std::cout << "float: nanf" << std::endl;
                std::cout << "double: nan" << std::endl;
            } else if (literal == "+inf" || literal == "+inff") {
                std::cout << "float: +inff" << std::endl;
                std::cout << "double: +inf" << std::endl;
            } else if (literal == "-inf" || literal == "-inff") {
                std::cout << "float: -inff" << std::endl;
                std::cout << "double: -inf" << std::endl;
            }
            break;
        }
        case IMPOSSIBLE:{
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: impossible" << std::endl;
            std::cout << "double: impossible" << std::endl;
            break;
        }
        default:
            std::cout << "Unknown type" << std::endl;
            break;
    }
}