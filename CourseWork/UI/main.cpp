#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <wingdi.h>
#include <math.h>

#include "../Core/cntrep.h"

using namespace std;

#define IDC_ARRAY_LENGTH        1000
#define IDC_REPETITIONS_AMOUNT  1001
#define IDC_VALUES_RANGE_MIN    1002
#define IDC_VALUES_RANGE_MAX    1003
#define IDC_SLOW_GEN_SPEED      1004
#define IDC_GEN_ARRAY           1005
#define IDC_WRITE_TO_FILE       1006
#define IDC_ARRAY_OUTPUT        1007
#define IDC_FILL_TABLE          1008



#define INPUT_MAX_LENGTH 25

NAMINGS MY_NAMINGS;
GENERATION_PARAMS_STRUCT GENERATION_PARAMS;

HWND hMainWindow;
HINSTANCE hMainWindowInstance;

// Input controls
HWND hArrayLengthInput;
HWND hRepetitionsAmountInput;
HWND hValuesRangeInputMin;
HWND hValuesRangeInputMax;
HWND hSlowGenSpeedInput;

//Buton controls
HWND hGenerateArrayBtn;
HWND hWriteToFileBtn;
HWND hFillTableBtn;

//Output 
HWND hArrayOutputEdit;

// Table
RECT* TABLE;

// Table cell
typedef struct {
    int width;
    int height;
} tableCellSize;

void setRectCoords(RECT *rect, LONG top, LONG left, LONG right, LONG bottom);
void createLabels(HWND hWnd, HINSTANCE wndInstance) ;
void createInputs(HWND hWnd, HINSTANCE wndInstance);
void createButtons(HWND hWnd, HINSTANCE wndInstance);
void createArrayOutput(HWND hWnd, HINSTANCE wndInstance);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
RECT* createTable(int x, int y, int width, int height, int uniqueRandomValuesArrayLength);
void infoTable(RECT *table, int tableSize);
tableCellSize calcTableCellSize(int tableWidth, int tableHeight, int elementsAmount);
void showTable(HDC hdc, RECT* table, int tableSize);
void writeTableValues(HDC hdc, int* uniqueRandomValuesArray, RECT* table, int tableSize);
COLORREF* generateTableColors(int uniqueRandomValuesArrayLength);
int findIndex(int* array, int arrLength, int number);
void fillTable(HWND hWnd, HDC hdc, RECT* table, int* repetitionsCountingArray, int repetitionCountingArrayLength, int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, COLORREF* tableColors, int generationSpeed);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    fillNamingsUS(&MY_NAMINGS);
    HBRUSH mainWindowBackgroundColor;
    mainWindowBackgroundColor = CreateSolidBrush(RGB(255, 255, 255));
    const wchar_t MAIN_WINDOW_CLASS_NAME[]  = L"Main Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = MAIN_WINDOW_CLASS_NAME;
    wc.hbrBackground = (HBRUSH)mainWindowBackgroundColor;
    wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
    
    if (!RegisterClass(&wc))
        return -1;


    HWND hMainWindow = CreateWindowEx(
        0,
        MAIN_WINDOW_CLASS_NAME,
        L"Repetition counting",
        WS_OVERLAPPEDWINDOW,

        200, 50, 1400, 950,

        NULL, 
        NULL,
        hInstance,
        NULL
        );

    if (hMainWindow == NULL)
    {
        return 0;
    }

    hMainWindowInstance =  wc.hInstance;

    ShowWindow(hMainWindow, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE: 
    {
        createLabels(hWnd, hMainWindowInstance);
        hMainWindow = hWnd;
        createInputs(hWnd, hMainWindowInstance);
        createButtons(hWnd, hMainWindowInstance);
        createArrayOutput(hWnd, hMainWindowInstance);
        EnableWindow(hWriteToFileBtn, false);
        EnableWindow(hFillTableBtn, false);
        InvalidateRect(hWnd, NULL, false);
        break; 
    }  
    case WM_COMMAND: 
        if (LOWORD(wParam) == IDC_GEN_ARRAY) {
            wchar_t* arrayLength = (wchar_t*)malloc(sizeof(wchar_t*));
            wchar_t* repetitionsAmount = (wchar_t*)malloc(sizeof(wchar_t*));
            wchar_t* valueRangeMin = (wchar_t*)malloc(sizeof(wchar_t*));
            wchar_t* valueRangeMax = (wchar_t*)malloc(sizeof(wchar_t*));
            wchar_t* slowGenSpeed = (wchar_t*)malloc(sizeof(wchar_t*));
            GetWindowText(hArrayLengthInput, arrayLength, INPUT_MAX_LENGTH);
            GetWindowText(hRepetitionsAmountInput, repetitionsAmount, INPUT_MAX_LENGTH);
            GetWindowText(hValuesRangeInputMin, valueRangeMin, INPUT_MAX_LENGTH);
            GetWindowText(hValuesRangeInputMax, valueRangeMax, INPUT_MAX_LENGTH);
            GetWindowText(hSlowGenSpeedInput, slowGenSpeed, INPUT_MAX_LENGTH);

            ERRORS_ENUM errs = checkErrors(arrayLength, repetitionsAmount, valueRangeMin, valueRangeMax, slowGenSpeed);
            

            switch(errs) 
            {
                case INVALID_VALUE:
                    MessageBox(hWnd, L"Some of values are invalid", L"Invalid value", MB_ICONERROR); 
                    break;
                case INCOMPATIBLE_VALUES_RANGE:
                    MessageBox(hWnd, L"Incompatible range of values(mb min value is equals or more than max value)", L"Incompatible vlaues range", MB_ICONERROR);
                    break;
                case INVALID_ARRAY_LENGTH:
                    MessageBox(hWnd, L"Array length is not divided by modulus by repetitions amount", L"Invalid array length", MB_ICONERROR);
                    break;
                case INVALID_VALUES_RANGE_LENGTH: 
                    MessageBox(hWnd, L"Not enough values in values range to fill the array", L"Invalid values range length", MB_ICONERROR);
                    break;
                case VALID:
                    calcArray(arrayLength, repetitionsAmount, valueRangeMin, valueRangeMax, slowGenSpeed);
                    writeArrayToOutput(hArrayOutputEdit, UNIQUE_RANDOM_VALUES_ARRAY_COPY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY, L"Array of random values:");
                    appendArrayToOutput(hArrayOutputEdit, REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH, L"Repetition counting array:");
                    EnableWindow(hWriteToFileBtn, true);
                    EnableWindow(hFillTableBtn, true);
                    TABLE = createTable(700, 100, 500, 500, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY);
                    break;
            }
          
            free(arrayLength);
            free(repetitionsAmount);
            free(valueRangeMin);
            free(valueRangeMax);
            free(slowGenSpeed);
        }
        if (LOWORD(wParam) == IDC_WRITE_TO_FILE) 
        {
            writeToFile(UNIQUE_RANDOM_VALUES_ARRAY_COPY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY, REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH, "Output.txt");
            MessageBox(hMainWindow, L"Successfully write to file", L"Write to file", MB_OK);
        }
        if (LOWORD(wParam) == IDC_FILL_TABLE)
        {
            TABLE_COLORS = generateTableColors(UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY);
            HDC dc = GetDC(hWnd);
                wchar_t* slowGenSpeed = (wchar_t*)malloc(sizeof(wchar_t*));
                GetWindowText(hSlowGenSpeedInput, slowGenSpeed, INPUT_MAX_LENGTH);
                fillTable(hWnd, dc, TABLE, REPETITION_COUNTING_ARRAY, REPETITION_COUNTING_ARRAY_LENGTH, UNIQUE_RANDOM_VALUES_ARRAY_COPY, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY, TABLE_COLORS, _wtoi(slowGenSpeed));
                free(slowGenSpeed);
            ReleaseDC(hWnd, dc);
        }
        break;
    case WM_DESTROY:
        clearData();
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
                // showTable(hdc, TABLE, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY);
                // writeTableValues(hdc, UNIQUE_RANDOM_VALUES_ARRAY_COPY, TABLE, UNIQUE_RANDOM_VALUES_ARRAY_LENGTH_COPY);
            EndPaint(hWnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void setRectCoords(RECT* rect, LONG top, LONG left, LONG right, LONG bottom) 
{   
    rect->top = top;
    rect->left = left;
    rect->right = right;
    rect->bottom = bottom;
}

void createLabels(HWND hWnd, HINSTANCE wndInstance) 
{  
    CreateWindow(L"static", MY_NAMINGS.ARRAY_LENGTH, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 30, 130, 20, hWnd, NULL, wndInstance, NULL); 
    CreateWindow(L"static", MY_NAMINGS.REPETITIONS_AMOUNT, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 100, 150, 20, hWnd, NULL, wndInstance, NULL);
    CreateWindow(L"static", MY_NAMINGS.VALUES_RANGE, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 170, 120, 20, hWnd, NULL, wndInstance, NULL);
    CreateWindow(L"static", MY_NAMINGS.SLOW_GENERATION_SPEED, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 250, 200, 20, hWnd, NULL, wndInstance, NULL);
    CreateWindow(L"static", MY_NAMINGS.ARRAY_OUTPUT, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 550, 120, 20, hWnd, NULL, wndInstance, NULL);
}

void createInputs(HWND hWnd, HINSTANCE wndInstance)
{
    hArrayLengthInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"20", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 50, 200, 25, hWnd, (HMENU)IDC_ARRAY_LENGTH, wndInstance, NULL);
    hRepetitionsAmountInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"4", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 120, 200, 25, hWnd, (HMENU)IDC_REPETITIONS_AMOUNT, wndInstance, NULL);
    hValuesRangeInputMin = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 190, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MIN, wndInstance, NULL);
    hValuesRangeInputMax = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"10", WS_VISIBLE | WS_CHILD | ES_LEFT, 250, 190, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MAX, wndInstance, NULL);
    hSlowGenSpeedInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"1", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 270, 200, 25, hWnd, (HMENU)IDC_SLOW_GEN_SPEED, wndInstance, NULL);
}

void createButtons(HWND hWnd, HINSTANCE wndInstance)
{
    hGenerateArrayBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", MY_NAMINGS.GENERATE_ARRAY, WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 350, 500, 60, hWnd, HMENU(IDC_GEN_ARRAY), wndInstance, NULL);
    hWriteToFileBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", MY_NAMINGS.WRITE_TO_FILE, WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 450, 500, 60, hWnd, HMENU(IDC_WRITE_TO_FILE), wndInstance, NULL);
    hFillTableBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", MY_NAMINGS.FILL_TABLE, WS_VISIBLE | WS_CHILD | ES_LEFT, 750, 800, 500, 60, hWnd, HMENU(IDC_FILL_TABLE), wndInstance, NULL);
}

void createArrayOutput(HWND hWnd, HINSTANCE wndInstance) 
{
    hArrayOutputEdit = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL, 30, 
                600, 500, 200, hWnd, (HMENU) IDC_ARRAY_OUTPUT, wndInstance, NULL);
}



RECT* createTable(int x, int y, int width, int height, int uniqueRandomValuesArrayLength)
{
    RECT* table = (RECT*)calloc(sizeof(RECT), uniqueRandomValuesArrayLength);
    tableCellSize tableCellSize = calcTableCellSize(width, height, uniqueRandomValuesArrayLength);
    int rowsAmount = height / tableCellSize.height;
    int colsAmount = width / tableCellSize.width;
    int rowNumber = 0;
    
    for (int i = 0; i < uniqueRandomValuesArrayLength; ++i) 
    {
        if (i != 0 && i % colsAmount == 0) 
        {
            ++rowNumber;
        }
        table[i].top = y + tableCellSize.height * rowNumber;
        table[i].bottom = y + tableCellSize.height * rowNumber + tableCellSize.height;
        table[i].left = x + tableCellSize.width * (i % colsAmount);
        table[i].right = x + tableCellSize.width * (i % colsAmount) + tableCellSize.width;
    }
    return table;
}

void infoTable(RECT *table, int tableSize)
{
    for (int i = 0; i < tableSize; ++i) 
    {
        printf("TableCell[%d]: top: %d, bottom: %d, left: %d, right: %d\n", i, table[i].top, table[i].bottom, table[i].left, table[i].right);
    }
}

tableCellSize calcTableCellSize(int tableWidth, int tableHeight, int elementsAmount)
{
    tableCellSize tableCellSize;
    int tableCellSquare = (tableWidth * tableHeight) / elementsAmount;
    tableCellSize.width = tableWidth / (int)sqrt(elementsAmount);
    tableCellSize.height = tableCellSquare / tableCellSize.width;
    return tableCellSize;
}

void writeTableValues(HDC hdc, int* uniqueRandomValuesArray, RECT* table, int tableSize) 
{
    for (int i = 0; i < tableSize; ++i) 
    {
        DrawTextW(hdc, to_wstring(uniqueRandomValuesArray[i]).c_str(), -1, &table[i], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    }
}

void showTable(HDC hdc, RECT* table, int tableSize) 
{
    if (!table) return;
    for (int i = 0; i < tableSize; ++i) 
    {
        Rectangle(hdc, table[i].left, table[i].top, table[i].right, table[i].bottom);
    }
}

COLORREF* generateTableColors(int uniqueRandomValuesArrayLength)
{
    COLORREF* colorsArr = (COLORREF*)calloc(sizeof(COLORREF), uniqueRandomValuesArrayLength);
    for (int i = 0; i < uniqueRandomValuesArrayLength; ++i)
    {
        colorsArr[i] = rand() % 256;
    }
    return colorsArr;
}

int findIndex(int* array, int arrLength, int number)
{
    for (int i = 0; i < arrLength; ++i) 
    {
        if (array[i] == number) 
        {
            return i;
        } 
    }
    return 0;
}

void fillTable(HWND hWnd, HDC hdc, RECT* table, int* repetitionsCountingArray, int repetitionCountingArrayLength, int* uniqueRandomValuesArray, int uniqueRandomValuesArrayLength, COLORREF* tableColors, int generationSpeed)
{
    InvalidateRect(hWnd, NULL, false);
    int index;
    HBRUSH brush;
    srand(time(NULL));
    for (int i = 0; i < repetitionCountingArrayLength; ++i) 
    {
        Sleep(generationSpeed);
        index = findIndex(uniqueRandomValuesArray, uniqueRandomValuesArrayLength, repetitionsCountingArray[i]);
        printf("index: %d\n", index);
        brush = CreateSolidBrush(tableColors[index]);
        (HBRUSH)SelectObject(hdc, brush);
        Rectangle(hdc, table[index].left, table[index].top, table[index].right, table[index].bottom);
        DrawTextW(hdc, to_wstring(repetitionsCountingArray[i]).c_str(), -1, &table[index], DT_CENTER | DT_SINGLELINE | DT_VCENTER);
    }
    DeleteObject(brush);
}