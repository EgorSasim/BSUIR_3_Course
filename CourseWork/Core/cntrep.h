#ifndef CNTREP_H
#define CNTREP_H
#endif

#include "../Typings/typings.h"

using namespace std;

typedef struct 
{
	int Low;
	int High;
} NumRange;

NumRange randNumRange;

int *REPETITION_COUNTING_ARRAY;
int REPETITION_COUNTING_ARRAY_LENGTH;
int REPETITION_AMOUNT;
int *UNIQUE_RANDOM_VALUES_ARRAY;
int UNIQUE_RANDOM_VALUES_ARRAY_LENGTH;
int *UNIQUE_RANDOM_VALUES_ARRAY_COPY;
int UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY;
int *UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY;
int UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH;



int* initArray(int arrayLength);

void fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength, 
								int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength,
								int* uniqueRadomValuesRepetitionAmountArray, int uniqueRadomValuesRepetitionAmountArrayLength,
								int repetitionAmount);
int showArray(int* repetitionCountingArray, int arrayLength);
void generateUniqueRandomValues(int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, NumRange randNumRange);
int isUniqueNumber(int* uniqueValuesArray, int uniqueValuesArrayLength, int number);
void shiftArrayLeft(int* array, int arrayLength, int pos);
bool isNumber(char number[]);
ERRORS_ENUM checkErrors(wchar_t* arrayLength, wchar_t* repetitionsAmount, wchar_t* valueRangeMin, wchar_t* valueRangeMax, wchar_t* slowGenSpeed);
void calcArray(wchar_t* arrayLength, wchar_t* repetitionsAmount, wchar_t* valueRangeMin, wchar_t* valueRangeMax, wchar_t* slowGenSpeed);
void writeArrayToOutput(HWND hWnd, int* array, int arrayLength, wstring title);
void appendArrayToOutput(HWND hWnd, int* array, int arrayLength, wstring title);
void copyArr(int *sourceArr, int *destArr, int arrLength);
void clearData();


int* initArray(int arrayLength)
{
	return (int *)calloc(arrayLength, sizeof (int));
}

void fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength, 
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

void generateUniqueRandomValues(int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, NumRange randNumRange)
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


ERRORS_ENUM checkErrors(wchar_t* arrayLength, wchar_t* repetitionsAmount, wchar_t* valueRangeMin, wchar_t* valueRangeMax, wchar_t* slowGenSpeed) 
{
	int _arrayLength = _wtoi(arrayLength);
	int _repetitionsAmount = _wtoi(repetitionsAmount);
	int _valueRangeMin = _wtoi(valueRangeMin);
	int _valueRangeMax = _wtoi(valueRangeMax);
	int _slowGenSpeed = _wtoi(slowGenSpeed);

	if (_arrayLength <= 0 || _repetitionsAmount <= 0 || _valueRangeMin <= 0 || _valueRangeMax <= 0) 
	{
		return INVALID_VALUE;
	}
	if (_slowGenSpeed < 0) 
	{
		return INVALID_VALUE;
	} 
	if (_valueRangeMin > _valueRangeMax) 
	{
		return INCOMPATIBLE_VALUES_RANGE;
	}
	if (_arrayLength %  _repetitionsAmount != 0) 
	{
		return INVALID_ARRAY_LENGTH;
	}
	if ( (_valueRangeMax - _valueRangeMin + 1) * _repetitionsAmount < _arrayLength) 
	{
		return INVALID_VALUES_RANGE_LENGTH;
	}
	else 
	{
		return VALID;
	}
}


void calcArray(wchar_t* arrayLength, wchar_t* repetitionsAmount, wchar_t* valueRangeMin, wchar_t* valueRangeMax, wchar_t* slowGenSpeed)
{
	if (REPETITION_COUNTING_ARRAY) 
	{
		clearData();
	}
	srand(time(NULL));

	int _arrayLength = _wtoi(arrayLength);
	int _repetitionsAmount = _wtoi(repetitionsAmount);
	int _valueRangeMin = _wtoi(valueRangeMin);
	int _valueRangeMax = _wtoi(valueRangeMax);
	int _slowGenSpeed = _wtoi(slowGenSpeed);
	
	REPETITION_COUNTING_ARRAY_LENGTH = _arrayLength;
	REPETITION_AMOUNT = _repetitionsAmount;
	randNumRange.Low = _valueRangeMin;
	randNumRange.High = _valueRangeMax;

	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH = 
	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY = UNIQUE_RANDOM_VALUES_ARRAY_LENGTH = REPETITION_COUNTING_ARRAY_LENGTH / REPETITION_AMOUNT;
	
	UNIQUE_RANDOM_VALUES_ARRAY = initArray(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
	UNIQUE_RANDOM_VALUES_ARRAY_COPY = initArray(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY);
	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY = initArray(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH);
	REPETITION_COUNTING_ARRAY = initArray(REPETITION_COUNTING_ARRAY_LENGTH);
	
	generateUniqueRandomValues(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH, randNumRange);
	copyArr(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_COPY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
	printf("Random values: \n");
	showArray(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
	fillRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH,
								UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH,
								UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY, UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH,
								REPETITION_AMOUNT);
	printf("Repetition counting array:\n\n");
	showArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	
	return;
}

void writeArrayToOutput(HWND hWnd, int* array, int arrayLength, wstring title)
{
	wstring output = L"";

	output += title + L"\r\n";

	for (int i = 0; i < arrayLength; ++i) 
	{
		output += to_wstring(array[i]);
		output += L"\r\n";
	}
	SetWindowText(hWnd, output.c_str());
}

void appendArrayToOutput(HWND hWnd, int* array, int arrayLength, wstring title)
{
	wstring output = L"";
	output += title + L"\r\n";

	for (int i = 0; i < arrayLength; ++i) 
	{
		output += to_wstring(array[i]);
		output += L"\r\n";
	}
    int TextLen = SendMessageW(hWnd, WM_GETTEXTLENGTH, 0, 0);
    SendMessageW(hWnd, EM_SETSEL, (WPARAM)TextLen, (LPARAM)TextLen);
    SendMessageW(hWnd, EM_REPLACESEL, FALSE, (LPARAM)output.c_str());
}

void copyArr(int *sourceArr, int *destArr, int arrLength)
{
	for (int i = 0; i < arrLength; ++i) 
	{
		*(destArr + i) = *(sourceArr + i);
	}
}

void clearData() 
{
	free(REPETITION_COUNTING_ARRAY);
	free(UNIQUE_RANDOM_VALUES_ARRAY);
	free(UNIQUE_RANDOM_VALUES_ARRAY_COPY);
	free(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY);
	REPETITION_COUNTING_ARRAY_LENGTH = 0;
	REPETITION_AMOUNT = 0;
	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH = 0;
	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY = 0;
	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH = 0;
}