#include <iostream>
#include <stdlib.h>
#include <ctype.h>

int *REPETITION_COUNTING_ARRAY;
int REPETITION_COUNTING_ARRAY_LENGTH;
int REPETITION_AMOUNT;
int *UNIQUE_RANDOM_VALUES_ARRAY;
int UNIQUE_RANDOM_VALUES_ARRAY_LENGTH;


int* initRepetitionCountingArray(int arrayLength);
int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength);
int showRepetitionCountingArray(int* repetitionCountingArray, int arrayLength);
bool isNumber(char number[]);
int* initUniqueRandomValuesArray(int arrayLength);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (argc < 3)
	{	
		printf("Not enough parameters. Should be at least 2:\n1. Array size\n2. Repetition amount\n");
		return -1;
	}
	if (!isNumber(argv[1]) || !isNumber(argv[2]))
	{
		printf("Incorrect parameters values(you should pass two numbers)\n");
		return -1;
	}
	
	REPETITION_COUNTING_ARRAY_LENGTH = atoi(argv[1]);
	REPETITION_AMOUNT = atoi(argv[2]);

	if (REPETITION_COUNTING_ARRAY_LENGTH <= 0 || REPETITION_AMOUNT <= 0)
	{
		printf("Arguments values should be more than zero\n");
		return -1;
	}
	if (REPETITION_COUNTING_ARRAY_LENGTH % REPETITION_AMOUNT != 0) 
	{
		printf("Array length should be divided by repetitions amount without rest\n");
		return -1;
	}

	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH = REPETITION_COUNTING_ARRAY_LENGTH / REPETITION_AMOUNT;
	UNIQUE_RANDOM_VALUES_ARRAY = initUniqueRandomValuesArray(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);

	REPETITION_COUNTING_ARRAY = initRepetitionCountingArray(REPETITION_COUNTING_ARRAY_LENGTH);
	fillRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	showRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	free(REPETITION_COUNTING_ARRAY);
	return 0;
}

int* initRepetitionCountingArray(int arrayLength)
{
	return (int *)calloc(arrayLength, sizeof (int));
}

int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength)
{
	for (int i = 0; i < arrayLength; ++i)
	{
		repetitionCountingArray[i] = rand() % 100;
	}
	return 0;
}

int showRepetitionCountingArray(int* repetitionCountingArray, int arrayLength)
{

	for (int i = 0; i < arrayLength; ++i)
	{
		printf("Array[%d]: %d\n", i, repetitionCountingArray[i]);
	}
	printf("that's all\n");
	return 0;
}

bool isNumber(char number[])
{
	int i = 0;
	if (number[0] == '-')
		i = 1;
	for (; number[i] != 0; ++i)
	{
		if (!isdigit(number[i]))
			return 0;
	}
	return 1;
}

int* initUniqueRandomValuesArray(int arrayLength)
{
	return (int *)calloc(arrayLength, sizeof (int));
}


