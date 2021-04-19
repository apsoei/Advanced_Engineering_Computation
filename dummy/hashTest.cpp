#include <iostream>

int main(void)
{
    std::hash <std::string> func;
    std::cout << func("a") << std::endl; 
    std::cout << func("b") << std::endl; 
    std::cout << func("c") << std::endl; 
}