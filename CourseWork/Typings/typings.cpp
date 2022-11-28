#include <iostream>

using namespace std;

struct NAMINGS {
    const wchar_t* ARRAY_LENGTH;
    const wchar_t* REPETITIONS_AMOUNT;
    const wchar_t* VALUES_RANGE;
    const wchar_t* SLOW_GENERATION_SPEED;
    const wchar_t* GENERATE_ARRAY;
    const wchar_t* WRITE_TO_FILE;
    const wchar_t* VALUES_TABLE;
};

typedef struct  {
    int ARRAY_LENGTH;
    int REPETITIONS_AMOUNT;
    int VALUES_RANGE_MIN;
    int VALUES_RANGE_MAX;
    int SLOW_GEN_SPEED;
} GENERATION_PARAMS_STRUCT;

typedef enum {
    INVALID_VALUE,
    INVALID_ARRAY_LENGTH,
    INCOMPATIBLE_VALUES_RANGE,
    INVALID_VALUES_RANGE_LENGTH,
    VALID,
} ERRORS_ENUM;

void fillNamingsUS(NAMINGS *namings);

void fillNamingsUS(NAMINGS *namings) 
{
    namings->ARRAY_LENGTH = L"Array length: ";
    namings->REPETITIONS_AMOUNT = L"Repetitions amount: ";
    namings->VALUES_RANGE = L"Values range: ";
    namings->SLOW_GENERATION_SPEED = L"Slow generation speed by \'n\' times: ";
    namings->GENERATE_ARRAY = L"Generate array";
    namings->WRITE_TO_FILE = L"Write to file";
    namings->VALUES_TABLE = L"Values table";
}


