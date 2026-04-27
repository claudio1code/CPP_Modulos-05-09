#include "identify.hpp"
#include  <cstdlib>
#include <iostream>
#include <ctime>
#include <exception>
#include "Base.hpp"
int main() {
    std::srand(time(NULL));
    Base* p = generate();
    std::cout << "Testing identify with pointer: ";
    identify(p);
    std::cout << "Testing identify with reference: ";
    identify(*p);
    delete p;
    return 0;
}
  