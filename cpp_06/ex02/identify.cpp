#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <exception>

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p)) std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p)) std::cout << "C" << std::endl;
}

void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::exception& e) {}
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return; 
    } catch (std::exception& e) {}
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (std::exception& e) {}
}

Base* generate(void) {
    int random = std::rand() % 3;
    if (random == 0) return new A();
    if (random == 1) return new B();
    return new C();
}
