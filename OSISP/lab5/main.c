#include <stdio.h>
#include <windows.h>
#include <string.h>

#define WORD_SIZE 128
#define BUFFER_SIZE 1024 * 1024
#define THREAD_COUNT 3

HANDLE hMutex;
HANDLE hThreads[THREAD_COUNT];

typedef void TSort(char**, int, int);

typedef struct QueueNodeStruct
{
	char** words;
	int startIndex;
	int endIndex;
	TSort* task;
	struct QueueNodeStruct* next;
} QueueNode;

typedef struct EnqueueParamsStruct
{
	char** words;
	int startIndex;
	int endIndex;
	TSort* task;
} EnqueueParams;

QueueNode* head = NULL;
char*** chunks = NULL;
int* chunkCount;

int CountWords(char*);
char** BreakBufferInWords(char*);
char*** BreakWordsInChunks(char**, char*);
void QuickSort(char** chunk, int first, int last);
DWORD WINAPI Enqueue(LPVOID);
DWORD WINAPI ProcessQueue(LPVOID);
char** MergeArrays(char** arr1, char** arr2, int arrLen1, int arrLen2);
void WriteToResultFile(char**, int);

int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);
	HANDLE hFile = CreateFile("input.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	char buffer[BUFFER_SIZE];
	DWORD dwBytesRead = 0;
	ReadFile(hFile, buffer, BUFFER_SIZE - 1, &dwBytesRead, NULL);
	buffer[dwBytesRead] = '\0';
	char** words = BreakBufferInWords(buffer);
	chunks = BreakWordsInChunks(words, buffer);
	int wordsPerChunk = CountWords(buffer) / THREAD_COUNT;
	int wordsInLastChunk = CountWords(buffer) - (THREAD_COUNT - 1) * wordsPerChunk;
	//adding to queue
	for (int i = 0; i < THREAD_COUNT - 1; i++)
	{
		EnqueueParams params = { chunks[i], 0, wordsPerChunk, QuickSort };
		hThreads[i] = CreateThread(NULL, 0, &Enqueue, &params, 0, NULL);
		Sleep(200);
	}
	WaitForMultipleObjects(THREAD_COUNT, hThreads, TRUE, INFINITE);
	EnqueueParams lastChunkParams = { chunks[THREAD_COUNT - 1], 0, wordsInLastChunk, QuickSort };
	hThreads[THREAD_COUNT - 1] = CreateThread(NULL, 0, &Enqueue, &lastChunkParams, 0, NULL);
	WaitForSingleObject(hThreads[THREAD_COUNT - 1], INFINITE);
	QueueNode* tmp = head;
	//sorting
	for (int i = 0; i < THREAD_COUNT; i++)
	{
		hThreads[i] = CreateThread(NULL, 0, &ProcessQueue, tmp, 0, NULL);
		tmp = tmp->next;
	}
	WaitForMultipleObjects(THREAD_COUNT, hThreads, TRUE, INFINITE);
	tmp = head;
	int currentLength = 0;
	char** result = MergeArrays(NULL, tmp->words, 0, tmp->endIndex);
	currentLength += tmp->endIndex;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		result = MergeArrays(result, tmp->words, currentLength, tmp->endIndex);
		currentLength += tmp->endIndex;
		tmp = tmp->next;
	}
	WriteToResultFile(result, CountWords(buffer));
	printf("Success\n");
	return 0;
}

int CountWords(char* buffer)
{
	int count = 0;
	char* tmp = buffer;
	while ((*tmp))
	{
		if ((*tmp) == '\n')
			count++;
		tmp++;
	}
	return count;
}

char** BreakBufferInWords(char* buffer)
{
	char** result = (char**) malloc (sizeof(char*) * CountWords(buffer));
	for (int i = 0; i < CountWords(buffer); i++)
		result[i] = (char*) malloc (sizeof(char) * WORD_SIZE);
	char* tmp = buffer;
	char* wordBeginning = buffer;
	int count = 0;
	while ((*tmp))
	{
		if ((*tmp) == '\n')
		{
			memcpy(result[count], wordBeginning, tmp - wordBeginning + 1);
			result[count][tmp - wordBeginning + 1] = '\0';
			tmp++;
			wordBeginning = tmp;
			count++;
		}
		tmp++;
	}
	return result;
}

char*** BreakWordsInChunks(char** words, char* buffer)
{
	char*** result = (char***) malloc (sizeof(char**) * THREAD_COUNT);
	int count = 0;
	int totalWordCount = CountWords(buffer);
	int wordCountPerChunk = totalWordCount / THREAD_COUNT;
	for (int i = 0; i < THREAD_COUNT - 1; i++)
	{
		result[i] = (char**) malloc(sizeof(char*) * wordCountPerChunk);
		for (int j = 0; j < wordCountPerChunk; j++)
		{
			result[i][j] = (char*) malloc (sizeof(char) * WORD_SIZE);
			memcpy(result[i][j], words[count], strlen(words[count]));
			result[i][j][strlen(words[count])] = '\0';
			count++;
		}
	}
	int lastChunksSize = totalWordCount - (THREAD_COUNT - 1) * wordCountPerChunk;
	result[THREAD_COUNT - 1] = (char**) malloc(sizeof(char*) * lastChunksSize);
	for (int j = 0; j < lastChunksSize; j++)
	{
		result[THREAD_COUNT - 1][j] = (char*) malloc (sizeof(char) * WORD_SIZE);
		memcpy(result[THREAD_COUNT - 1][j], words[count], strlen(words[count]));
		result[THREAD_COUNT - 1][j][strlen(words[count])] = '\0';
		count++;
	}
	return result;
}

void QuickSort(char** chunk, int first, int last)
{
	int i, j, pivot;
	char* temp;
	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while ((strcmp(chunk[i], chunk[pivot]) < 0) && (i < last))
				i++;
			while ((strcmp(chunk[j], chunk[pivot])) > 0)
				j--;
			if (i < j)
			{
				temp = chunk[i];
				chunk[i] = chunk[j];
				chunk[j] = temp;
			}
		}
		temp = chunk[pivot];
		chunk[pivot] = chunk[j];
		chunk[j] = temp;
		QuickSort(chunk, first, j - 1);
		QuickSort(chunk, j + 1, last);
	}
}

DWORD WINAPI Enqueue(LPVOID params)
{
	WaitForSingleObject(hMutex, INFINITE);
	EnqueueParams* enqParams = (EnqueueParams*) params;
	if (head == NULL)
	{
		head = (QueueNode*) malloc (sizeof(QueueNode));
		head->words = enqParams->words;
		head->startIndex = enqParams->startIndex;
		head->endIndex = enqParams->endIndex;
		head->task = enqParams->task;
		head->next = NULL;
	}
	else
	{
		QueueNode* tmp = head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (QueueNode*) malloc(sizeof(QueueNode));
		tmp = tmp->next;
		tmp->words = enqParams->words;
		tmp->startIndex = enqParams->startIndex;
		tmp->endIndex = enqParams->endIndex;
		tmp->task = enqParams->task;
		tmp->next = NULL;
	}
	ReleaseMutex(hMutex);
}

DWORD WINAPI ProcessQueue(LPVOID params)
{
	WaitForSingleObject(hMutex, INFINITE);
	QueueNode* tmp = (QueueNode*) params;
	(tmp->task)(tmp->words, tmp->startIndex, tmp->endIndex - 1);
	tmp = tmp->next;
	ReleaseMutex(hMutex);
}

char** MergeArrays(char** arr1, char** arr2, int arrLen1, int arrLen2)
{
	char** result = (char**) malloc (sizeof(char*) * (arrLen1 + arrLen2));
	for (int i = 0; i < arrLen1 + arrLen2; i++)
	{
		result[i] = (char*) malloc (sizeof(char) * WORD_SIZE);
	}
	int i = 0, j = 0;
	while (i < arrLen1 && j < arrLen2)
	{
		if (strcmp(arr1[i], arr2[j]) < 0)
		{
			result[i + j] = arr1[i];
			i++;
		}
		else
		{
			result[i + j] = arr2[j];
			j++;
		}
	}
	while (i < arrLen1)
	{
		result[i + j] = arr1[i];
		i++;
	}
	while (j < arrLen2)
	{
		result[i + j] = arr2[j];
		j++;
	}
	return result;
}

void WriteToResultFile(char** result, int wordsCount)
{
	HANDLE hFile = CreateFile("output.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (int i = 0; i < wordsCount; i++)
	{
		WriteFile(hFile, result[i], strlen(result[i]), NULL, NULL);
	}
}