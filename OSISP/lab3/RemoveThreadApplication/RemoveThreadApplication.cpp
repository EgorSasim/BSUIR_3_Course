#include <iostream>
#include <string>
int main()
{
    std::string localString = "shrek2";
    std::cout << "Current local string: " << localString << std::endl;
    std::cin.get();
    std::cout << "Current local string: " << localString << std::endl;
    std::cin.get();
}