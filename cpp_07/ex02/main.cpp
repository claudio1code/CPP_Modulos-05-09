#include "Array.hpp"
#include <iostream>
#include <string>

int main(){
    std::cout << "--- Empty Array Test ---" << std::endl;
    Array<int> emptyArray;
    std::cout << "Size of empty array: " << emptyArray.size() << std::endl; 

    std::cout << "\n--- Integer Array Test ---" << std::endl;
    Array<int> intArray(5);
    for (unsigned int i = 0; i < intArray.size(); i++)
        intArray[i] = i * 10;
    std::cout << "Numbers: ";
    for (unsigned int i = 0; i < intArray.size(); i++)
        std::cout << intArray[i] << " ";
    std::cout << std::endl;

    std::cout << "\n--- Deep Copy Test ---" << std::endl;
    Array<int> copyArray = intArray;
    copyArray[0] = 999;
    std::cout << "Original first element: " << intArray[0] << 
    " (should be 0)" << std::endl;
    std::cout << "Copied first element: " << copyArray[0] << 
    " (should be 999)" << std::endl;

    std::cout << "\n--- Out of Range Test ---" << std::endl;
    try {
        std::cout << "Trying to acess index 10: " << std::endl;
        std::cout << intArray[10] << std::endl;
    } catch (const std::out_of_range &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << "\n--- String Array Test ---" << std::endl;
    Array<std::string> stringArray(3);
    stringArray[0] = "Hello";
    stringArray[1] = "World";
    stringArray[2] = "!";
    std::cout << stringArray[0] << " " 
              << stringArray[1] << stringArray[2] << std::endl; 
            return 0;
    }           