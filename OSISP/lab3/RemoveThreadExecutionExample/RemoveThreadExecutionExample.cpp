#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int GetProcessIdByName(const char* processName);

int main()
{
	int processId = GetProcessIdByName("RemoveThreadApplication.exe");
	if (processId == -1)
	{
		return -1;
	}
	const char* dllPath = "D:\\User Files\\University\\OsaSp\\lab3\\x64\\Debug\\StringReplaceDLL.dll";
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess == NULL)
	{
		std::cout << "Failed to open process, error code: " << GetLastError() << std::endl;
		return -1;
	}
	LPTSTR remoteLibFile = (LPTSTR)VirtualAllocEx(hProcess, NULL, lstrlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	if (remoteLibFile == NULL)
	{
		std::cout << "Failed VirtualAllocEx, error code: " << GetLastError() << std::endl;
		return -1;
	}
	if (WriteProcessMemory(hProcess, remoteLibFile, (void*)dllPath, lstrlen(dllPath) + 1, NULL) == 0)
	{
		std::cout << "Failed WriteProcessMemory, error code: " << GetLastError() << std::endl;
		return -1;
	}
	PTHREAD_START_ROUTINE startAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if (startAddress == NULL)
	{
		std::cout << "Failed GetProcAddress, error code: " << GetLastError() << std::endl;
		return -1;
	}
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, startAddress, remoteLibFile, 0, NULL);
	if (hThread == NULL)
	{
		std::cout << "Failed CreateRemoteThread, error code: " << GetLastError() << std::endl;
	}
}

int GetProcessIdByName(const char* processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 pe;
	int pid = -1;
	BOOL copyResult;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to get list of all processes, error code: " << GetLastError() << std::endl;
		return pid;
	}
	pe.dwSize = sizeof(PROCESSENTRY32);
	copyResult = Process32First(hSnapshot, &pe);
	while (copyResult)
	{
		if (strcmp(pe.szExeFile, processName) == 0)
		{
			pid = pe.th32ProcessID;
			CloseHandle(hSnapshot);
			return pid;
		}
		copyResult = Process32Next(hSnapshot, &pe);
	}
	CloseHandle(hSnapshot);
	std::cout << "Process not found" << std::endl;
	return pid;
}