// #include <iostream>
// #include <stdlib.h>
// #include <ctype.h>

// #include "cntrep.h"



// int main(int argc, char *argv[])
// {
// 	srand(time(NULL));
// 	if (argc < 3)
// 	{	
// 		printf("Not enough parameters. Should be at least 2:\n1. Array size\n2. Repetition amount\n");
// 		return -1;
// 	}
// 	if (!isNumber(argv[1]) || !isNumber(argv[2]))
// 	{
// 		printf("Incorrect parameters values(you should pass two numbers)\n");
// 		return -1;
// 	}
	
// 	REPETITION_COUNTING_ARRAY_LENGTH = atoi(argv[1]);
// 	REPETITION_AMOUNT = atoi(argv[2]);

// 	if (argv[3] && argv[4] && isNumber(argv[3]) && isNumber(argv[4]))
// 	{
// 		randNumRange.Low = atoi(argv[3]);
// 		randNumRange.High = atoi(argv[4]);
// 	}

// 	// REPETITION_COUNTING_ARRAY_LENGTH = 10;
// 	// REPETITION_AMOUNT = 2;

// 	if (REPETITION_COUNTING_ARRAY_LENGTH <= 0 || REPETITION_AMOUNT <= 0)
// 	{
// 		printf("Arguments values should be more than zero\n");
// 		return -1;
// 	}
// 	if (REPETITION_COUNTING_ARRAY_LENGTH % REPETITION_AMOUNT != 0) 
// 	{
// 		printf("Array length should be divided by repetitions amount without rest\n");
// 		return -1;
// 	}
	

// 	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH = 
// 	UNIQUE_RANDOM_VALUES_ARRAY_LENGTH = REPETITION_COUNTING_ARRAY_LENGTH / REPETITION_AMOUNT;
	
// 	UNIQUE_RANDOM_VALUES_ARRAY = initArray(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
// 	UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY = initArray(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH);
// 	REPETITION_COUNTING_ARRAY = initArray(REPETITION_COUNTING_ARRAY_LENGTH);
	
// 	generateUniqueRandomValues(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH, randNumRange);
// 	printf("Array of random values: \n");
// 	showArray(UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH);
// 	fillRepetitionCountingArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH,
// 								UNIQUE_RANDOM_VALUES_ARRAY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH,
// 								UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY, UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY_LENGTH,
// 								REPETITION_AMOUNT);
// 	printf("Array of repetition counting:\n\n");
// 	showArray(REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH);
	
// 	free(UNIQUE_RANDOM_VALUES_ARRAY);
// 	free(UNIQUE_RANDOM_VALUES_REPETITIONS_AMOUNT_ARRAY);
// 	free(REPETITION_COUNTING_ARRAY);
// 	return 0;
// }
