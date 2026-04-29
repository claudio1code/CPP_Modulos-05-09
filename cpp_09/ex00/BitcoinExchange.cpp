#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _data() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || year > 2026) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > 31) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    }
    return true;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()){
        throw std::runtime_error("Could not open file: " + filename);
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)){
        size_t command_pos = line.find(',');
        if (command_pos != std::string::npos){
            std::string date = line.substr(0, command_pos);
            std::string value_str = line.substr(command_pos + 1);
            float rate = static_cast<float>(std::atof(value_str.c_str()));
            this->_data[date] = rate;
        }
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()){
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)){
        if (line.empty()) continue;

        size_t command_pos = line.find('|');
        
        if (command_pos != std::string::npos && command_pos >= 1 && command_pos + 1 < line.length()){
            
            std::string date = line.substr(0, command_pos - 1);
            std::string value_str = line.substr(command_pos + 2);
            if (!isValidDate(date)){
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            float value = static_cast<float>(std::atof(value_str.c_str()));
            
            if (value < 0){
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }
            if (value > 1000){
                std::cerr << "Error: too large a number." << std::endl;
                continue;
            }
            
            std::map<std::string, float>::iterator it = this->_data.lower_bound(date);
            
            if (it != this->_data.end() && it->first == date){
                std::cout << date << " => " << value << " = " << value * it->second << std::endl;
            } else {
                if (it != this->_data.begin()){
                    --it;
                    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
                } else {
                    std::cerr << "Error: no exchange rate available for date: " << date << std::endl;
                }
            }
        } 
        else {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    file.close();
}
