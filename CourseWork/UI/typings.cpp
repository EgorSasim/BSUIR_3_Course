#include <iostream>

using namespace std;

struct NAMINGS {
    wchar_t* ARRAY_LENGTH;
    wchar_t* REPETITIONS_AMOUNT;
    wchar_t* VALUES_RANGE;
    wchar_t* SLOW_GENERATION_SPEED;
    wchar_t* GENERATE_ARRAY;
    wchar_t* WRITE_TO_FILE;
    wchar_t* VALUES_TABLE;
};

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


