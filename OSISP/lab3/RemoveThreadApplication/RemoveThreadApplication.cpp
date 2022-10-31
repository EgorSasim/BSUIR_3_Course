#include <iostream>
#include <string>
int main()
{
    std::string localString = "Here come the rain again";
    std::cout << "Current local string: " << localString << std::endl;
    std::cin.get();
    std::cout << "Current local string: " << localString << std::endl;
    std::cin.get();
}