#ifndef CNTREP_H
#define CNTREP_H
#endif

#include "../Typings/typings.h"

typedef struct 
{
	int Low;
	int High;
} NumRange;


int* initArray(int arrayLength);

int fillRepetitionCountingArray(int* repetitionCountingArray, int arrayLength, 
								int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength,
								int* uniqueRadomValuesRepetitionAmountArray, int uniqueRadomValuesRepetitionAmountArrayLength,
								int repetitionAmount);
int showArray(int* repetitionCountingArray, int arrayLength);
void generateUniqueRandomValues(int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, NumRange randNumRange);
int isUniqueNumber(int* uniqueValuesArray, int uniqueValuesArrayLength, int number);
void shiftArrayLeft(int* array, int arrayLength, int pos);
bool isNumber(char number[]);
ERRORS_ENUM checkErrors(wchar_t* arrayLength, wchar_t* repetitionsAmount, wchar_t* valueRangeMin, wchar_t* valueRangeMax, wchar_t* slowGenSpeed);
