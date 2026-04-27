#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>
#include <exception>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_back(50);

    try {
        std::cout << "Finding 3 in vector: " << *easyfind(v, 3) << std::endl;
        std::cout << "Finding 30 in list: " << *easyfind(l, 30) << std::endl;
        std::cout << "Finding 100 in vector: " << *easyfind(v, 100) << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
