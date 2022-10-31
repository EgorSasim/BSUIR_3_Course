#include <iostream>
#include <string>

extern "C" __declspec(dllimport) void Replace(const char* data, const char* replacment);

int main()
{
	std::string localString = "Makarena";
	std::cout << "Current local string: " << localString << std::endl;
	Replace(localString.c_str(), "Do it!!!");
	std::cout << "Local string after call Replace function: " << localString << std::endl;
}