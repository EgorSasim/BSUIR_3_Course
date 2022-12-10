#include <pch.h>
#include <vector>
extern "C" __declspec(dllexport) void Replace(const char* data, const char* replacment);

void Replace(const char* data, const char* replacement)
{
	HANDLE process = GetCurrentProcess();
	size_t len = strlen(data);
	size_t replacementLength = strlen(replacement);

	if (process == NULL)
		return;
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	MEMORY_BASIC_INFORMATION info;
	std::vector<char> chunk;
	char* p = 0;
	while (p < si.lpMaximumApplicationAddress)
	{
		if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
		{
			if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
			{
				p = (char*)info.BaseAddress;
				chunk.resize(info.RegionSize);
				SIZE_T bytesRead;
				if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
				{
					for (size_t i = 0; i < (bytesRead - len); ++i)
					{
						if (memcmp(data, &chunk[i], len) == 0)
						{
							char* ref = (char*)p + i;
							int j;
							for (j = 0; j < replacementLength; j++) {
								ref[j] = replacement[j];
							}
							for (; j < len; j++)
								ref[j] = '\0';

						}
					}
				}
			}
			p += info.RegionSize;
		}
	}
}