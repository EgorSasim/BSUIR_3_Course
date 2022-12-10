#include <iostream>
#include <string>
#include <windows.h>

typedef void __stdcall TReplace(const char* data, const char* replacement);

int main()
{
	std::string localString = "Smth in the way";
	HMODULE library = LoadLibrary(L"D:\\BSUIR_3_Course\\OSISP\\lab3\\x64\\Debug\\StringReplaceDLL.dll");
	if (library == NULL)
	{
		std::cout << "Failed to load library, error code: " << GetLastError() << std::endl;
		return -1;
	}
	TReplace* pReplace;
	pReplace = (TReplace*)GetProcAddress(library, "Replace");
	if (pReplace == NULL)
	{
		std::cout << "Failed GetProcAddress, error code: " << GetLastError() << std::endl;
		return -1;
	}
	std::cout << "Current local string: " << localString << std::endl;
	pReplace(localString.c_str(), "Peniroyal tea");
	std::cout << "Local string after Replace function: " << localString << std::endl;
	if (FreeLibrary(library) == 0)
	{
		std::cout << "Failed to free library, error code: " << GetLastError() << std::endl;
		return -1;
	}
	return 0;
}
