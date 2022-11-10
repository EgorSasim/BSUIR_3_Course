#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void searchForKey(HKEY key, char* subKey, char* keyToSearch);

LSTATUS status;

int main(int argc, char* argv[])
{
	char* subKey = argv[1];
	char* keyToSearch = argv[2];
	int index = 0;
	printf("1 - HKEY_CLASSES_ROOT\n2 - HKEY_CURRENT_USER\n3 - HKEY_LOCAL_MACHINE\n4 - HKEY_USERS\n5 - HKEY_CURRENT_CONFIG\n");
	scanf("%d", &index);
	fflush(stdin);
	switch(index)
	{
		case 1:
			searchForKey(HKEY_CLASSES_ROOT, subKey, keyToSearch);
			break;
		case 2:
			searchForKey(HKEY_CURRENT_USER, subKey, keyToSearch);
			break;
		case 3:
			searchForKey(HKEY_LOCAL_MACHINE, subKey, keyToSearch);
			break;
		case 4:
			searchForKey(HKEY_USERS, subKey, keyToSearch);
			break;
		case 5:
			searchForKey(HKEY_CURRENT_CONFIG, subKey, keyToSearch);
			break;
		default:
			printf("Invalid input\n");
			return -1;
	}
	return 0;
}

void searchForKey(HKEY predicatedKey, char* subKey, char* keyToSearch)
{
	HKEY hKey;
	DWORD subKeysCount;
	DWORD maxSubKeyLength;
	status = RegOpenKey(predicatedKey, subKey, &hKey);
	if (status != ERROR_SUCCESS)
	{
		return;
	}
	status = RegQueryInfoKey(hKey, NULL, NULL, NULL, &subKeysCount, &maxSubKeyLength, NULL, NULL, NULL, NULL, NULL, NULL);
	if (status != ERROR_SUCCESS)
	{
		return;
	}
	if (subKeysCount <= 0)
	{
		return;
	}
	char currentSubKey[MAX_PATH];
	for (int i = 0; i < subKeysCount; i++)
	{
		DWORD currentSubLen = MAX_PATH;
		status == RegEnumKeyEx(hKey, i, currentSubKey, &currentSubLen, NULL, NULL, NULL, NULL);
		if (status == ERROR_SUCCESS)
		{
			if (strcmp(currentSubKey, keyToSearch) == 0)
				printf("%s\\%s\n", subKey, currentSubKey);
			char subKeyPath[currentSubLen + strlen(subKey)];
			sprintf(subKeyPath, "%s\\%s", subKey, currentSubKey);
			searchForKey(predicatedKey, subKeyPath, keyToSearch);
		}
	}
}