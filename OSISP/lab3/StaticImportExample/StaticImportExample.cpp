#include <iostream>
#include <string>

extern "C" __declspec(dllimport) void Replace(const char* data, const char* replacment);

int main()
{
	std::string localString = "local string";
	std::cout << "Current local string: " << localString << std::endl;
	Replace(localString.c_str(), "new string");
	std::cout << "Local string after call Replace function: " << localString << std::endl;
}