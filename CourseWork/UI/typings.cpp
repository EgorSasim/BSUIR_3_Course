#include <iostream>

using namespace std;

struct NAMINGS {
    char* ARRAY_LENGTH;
    char* REPETITIONS_AMOUNT;
    char* VALUES_RANGE;
    char* SLOW_GENERATION_SPEED;
    char* GENERATE_ARRAY;
    char* WRITE_TO_FILE;
    char* VALUES_TABLE;
};

void fillNamingsUS(NAMINGS *namings);

void fillNamingsUS(NAMINGS *namings) 
{
    namings->ARRAY_LENGTH = "Array length: ";
    namings->REPETITIONS_AMOUNT = "Repetitions amount: ";
    namings->VALUES_RANGE = "Values range: ";
    namings->SLOW_GENERATION_SPEED = "Slow generation speed by \'n\' times: ";
    namings->GENERATE_ARRAY = "Generate array";
    namings->WRITE_TO_FILE = "Write to file";
    namings->VALUES_TABLE = "Values table";
}


