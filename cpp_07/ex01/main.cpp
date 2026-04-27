#include "iter.hpp"

void printInt(int &n){
    std::cout << n << " ";
}

int main( void ) {
    int arr[] = {1, 2, 3, 4, 5};
    ::iter(arr, 5, printInt);
    return (0);
}
