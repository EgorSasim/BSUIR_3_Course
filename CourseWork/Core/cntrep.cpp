#include <iostream>
#include <stdlib.h>
#include <ctype.h>

typedef struct 
{
	int Low;
	int High;
} RandNumRange;

RandNumRange randNumRange;

int *REPETITION_COUNTING_ARRAY;
int REPETITION_COUNTING_ARRAY_LENGTH;
int REPETITION_AMOUNT;
int *UNIQUE_RANDOM_VALUES_ARRAY;
int UNIQUE_RANDOM_VALUES_ARRAY_LENGTH;
int *UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY;
int UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH;

int* initArray(int arrayLength);

int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength, 
								int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength,
								int* uniqueRadomValuesRepetitionAmountArray, int uniqueRadomValuesRepetitionAmountArrayLength,
								int repetitionAmount);
int showArray(int* repetitionCountingArray, int arrayLength);
void generateUniqueRandomValues(int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, RandNumRange randNumRange);
int isUniqueNumber(int* uniqueValuesArray, int uniqueValuesArrayLength, int number);
void shiftArrayLeft(int* array, int arrayLength, int pos);
bool isNumber(char number[]);

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

	if (argv[3] && argv[4] && isNumber(argv[3]) && isNumber(argv[4]))
	{
		randNumRange.Low = atoi(argv[3]);
		randNumRange.High = atoi(argv[4]);
	}

	// REPETITION_COUNTING_ARRAY_LENGTH = 10;
	// REPETITION_AMOUNT = 2;

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
	

	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH = 
	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH = REPETITION_COUNTING_ARRAY_LENGTH / REPETITION_AMOUNT;
	
	UNIQUE_RANDOM_VALUES_ARRAY = initArray(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY = initArray(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH);
	REPETITION_COUNTING_ARRAY = initArray(REPETITION_COUNTING_ARRAY_LENGTH);
	
	generateUniqueRandomValues(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH, randNumRange);
	printf("Array of random values: \n");
	showArray(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
	fillRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH,
								UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH,
								UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY, UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH,
								REPETITION_AMOUNT);
	printf("Array of repetition counting:\n\n");
	showArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	
	free(UNIQUE_RANDOM_VALUES_ARRAY);
	free(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY);
	free(REPETITION_COUNTING_ARRAY);
	return 0;
}

int* initArray(int arrayLength)
{
	return (int *)calloc(arrayLength, sizeof (int));
}

int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength, 
								int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength,
								int* uniqueRadomValuesRepetitionAmountArray, int uniqueRadomValuesRepetitionAmountArrayLength,
								int repetitionAmount)
{
	int i = 0;
	int randIndex = 0;
	while (i < arrayLength)
	{
		randIndex = rand() % (uniqueRandomValuesArrayLength); // randIndex = rand() % (max - min + 1) + min	
		if (uniqueRadomValuesRepetitionAmountArray[randIndex] < repetitionAmount)
		{
			repetitionCountingArray[i] = uniqueRandomValuesArray[randIndex];
			uniqueRadomValuesRepetitionAmountArray[randIndex]++;
			i++;
			if (uniqueRadomValuesRepetitionAmountArray[randIndex] == repetitionAmount)
			{
				shiftArrayLeft(uniqueRadomValuesRepetitionAmountArray, uniqueRadomValuesRepetitionAmountArrayLength, randIndex);
				shiftArrayLeft(uniqueRandomValuesArray, uniqueRandomValuesArrayLength, randIndex);
				uniqueRandomValuesArrayLength--;
				uniqueRadomValuesRepetitionAmountArrayLength--;
			}
		} 
	}
	
	// for (int i = 0; i < arrayLength; ++i)
	// {
	// 	repetitionCountingArray[i] = rand() % 100;
	// }
	// return 0;
}

int showArray(int* repetitionCountingArray, int arrayLength)
{

	for (int i = 0; i < arrayLength; ++i)
	{
		printf("Array[%d]: %d\n", i, repetitionCountingArray[i]);
	}
	printf("that's all\n");
	return 0;
}

void generateUniqueRandomValues(int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, RandNumRange randNumRange)
{
	int i = 0;
	int randNum = 0;
	while (i < uniqueRandomValuesArrayLength)
	{
		randNum = rand() % (randNumRange.High - randNumRange.Low + 1) + randNumRange.Low;
		if (isUniqueNumber(uniqueRandomValuesArray, i, randNum) == -1) 
		{
			uniqueRandomValuesArray[i] = randNum;
			i++;
		}
	}
}

int isUniqueNumber(int* uniqueValuesArray, int uniqueValuesArrayLength, int number)
{
	for (int i = 0; i < uniqueValuesArrayLength; ++i)
	{
		if (number == uniqueValuesArray[i])
		{
			return i;
		}
	}
	return -1;
}

void shiftArrayLeft(int* array, int arrayLength, int pos)
{
	for (int i = pos; i < arrayLength; ++i) 
	{
		array[i] = array[i + 1];
	}
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

