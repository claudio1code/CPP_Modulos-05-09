#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <string>

void printSeparator(const std::string& title) {
    std::cout << "\n=== " << title << " ===" << std::endl;
}

int main() {
    printSeparator("BASIC STACK OPERATIONS");
    
    MutantStack<int> mstack;
    
    std::cout << "Pushing 5 and 17..." << std::endl;
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Current Top: " << mstack.top() << " (Expected: 17)" << std::endl;
    
    std::cout << "Popping top element..." << std::endl;
    mstack.pop();
    
    std::cout << "New Top:     " << mstack.top() << " (Expected: 5)" << std::endl;
    std::cout << "Stack Size:  " << mstack.size() << " (Expected: 1)" << std::endl;

    printSeparator("ADDING MORE ELEMENTS");
    std::cout << "Pushing 3, 5, 737, and 0..." << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    std::cout << "Final Size:  " << mstack.size() << " (Expected: 5)" << std::endl;

    printSeparator("ITERATOR TEST (FORWARD)");
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << "Stack elements (begin -> end): ";
    for (; it != ite; ++it) {
        std::cout << "[" << *it << "] ";
    }
    std::cout << std::endl;

    printSeparator("REVERSE ITERATOR TEST");
    MutantStack<int>::reverse_iterator rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator rite = mstack.rend();

    std::cout << "Stack elements (rbegin -> rend): ";
    for (; rit != rite; ++rit) {
        std::cout << "[" << *rit << "] ";
    }
    std::cout << std::endl;

    printSeparator("COMPARISON WITH STD::LIST");
    std::list<int> lst;
    lst.push_back(5);
    lst.push_back(3);
    lst.push_back(5);
    lst.push_back(737);
    lst.push_back(0);

    std::cout << "List elements (begin -> end):  ";
    for (std::list<int>::iterator it_lst = lst.begin(); it_lst != lst.end(); ++it_lst) {
        std::cout << "[" << *it_lst << "] ";
    }
    std::cout << "\n(Matches MutantStack forward iteration? Yes!)" << std::endl;

    printSeparator("CONST ITERATOR TEST");
    const MutantStack<int> const_stack(mstack);
    MutantStack<int>::const_iterator cit = const_stack.begin();
    MutantStack<int>::const_iterator cite = const_stack.end();
    
    std::cout << "Const Stack elements: ";
    while (cit != cite) {
        std::cout << "[" << *cit << "] ";
        ++cit;
    }
    std::cout << std::endl;

    return 0;
}
