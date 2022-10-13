#include <iostream>
#include <stdlib.h>

int *REPETITION_COUNTING_ARRAY;
int REPETITION_COUNTING_ARRAY_LENGTH;

int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength);
int showRepetitionCountingArray(int* repetitionCountingArray, int arrayLength);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (!argv[1])
	{	
		printf("Can't find counting array length\n");
		return -1;
	}

	REPETITION_COUNTING_ARRAY_LENGTH = atoi(argv[1]);
	REPETITION_COUNTING_ARRAY = (int *)calloc(REPETITION_COUNTING_ARRAY_LENGTH, sizeof (int));
	fillRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	showRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	return 0;
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
