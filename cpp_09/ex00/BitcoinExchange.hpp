#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <map>
# include <algorithm>
# include <fstream>
# include <sstream>
# include <stdexcept>

class BitcoinExchange {
    private:
        std::map<std::string, float> _data;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void loadDatabase(const std::string& filename);
        void processInput(const std::string& filename);
        bool isValidDate(const std::string& date);

};

#endif
