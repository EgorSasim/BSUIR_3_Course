#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <wingdi.h>

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
#define IDC_BUTTON  1010
#define IDC_STATIC  1011


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

//Output 
HWND hArrayOutputEdit;


void setRectCoords(RECT *rect, LONG top, LONG left, LONG right, LONG bottom);
void createLabels(HWND hWnd, HINSTANCE wndInstance, HDC hdc) ;
void createInputs(HWND hWnd, HINSTANCE wndInstance);
void createButtons(HWND hWnd, HINSTANCE wndInstance);
void createArrayOutput(HWND hWnd, HINSTANCE wndInstance);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

    if (!RegisterClass(&wc))
        return -1;


    HWND hMainWindow = CreateWindowEx(
        0,
        MAIN_WINDOW_CLASS_NAME,
        L"Repetition counting",
        WS_OVERLAPPEDWINDOW,

        200, 50, 1200, 950,

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
        HDC createDC = GetDC(hWnd);
        createLabels(hWnd, hMainWindowInstance, createDC);
        ReleaseDC(hWnd, createDC);
        hMainWindow = hWnd;
        createInputs(hWnd, hMainWindowInstance);
        createButtons(hWnd, hMainWindowInstance);
        createArrayOutput(hWnd, hMainWindowInstance);
        EnableWindow(hWriteToFileBtn, false);
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
        break;
    case WM_DESTROY:
        clearData();
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
              createLabels(hWnd, hMainWindowInstance, hdc);
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

void createLabels(HWND hWnd, HINSTANCE wndInstance, HDC hdc) 
{  
    SIZE labelSize;
    GetTextExtentPoint(hdc, MY_NAMINGS.ARRAY_LENGTH, wcslen(MY_NAMINGS.ARRAY_LENGTH), &labelSize);
    CreateWindow(L"static", MY_NAMINGS.ARRAY_LENGTH, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 30, labelSize.cx, labelSize.cy, hWnd, NULL, wndInstance, NULL); 
    GetTextExtentPoint(hdc, MY_NAMINGS.REPETITIONS_AMOUNT, wcslen(MY_NAMINGS.REPETITIONS_AMOUNT), &labelSize);
    CreateWindow(L"static", MY_NAMINGS.REPETITIONS_AMOUNT, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 100, labelSize.cx, labelSize.cy, hWnd, NULL, wndInstance, NULL);
    GetTextExtentPoint(hdc, MY_NAMINGS.VALUES_RANGE, wcslen(MY_NAMINGS.VALUES_RANGE), &labelSize);
    CreateWindow(L"static", MY_NAMINGS.VALUES_RANGE, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 170, labelSize.cx, labelSize.cy, hWnd, NULL, wndInstance, NULL);
    GetTextExtentPoint(hdc, MY_NAMINGS.SLOW_GENERATION_SPEED, wcslen(MY_NAMINGS.SLOW_GENERATION_SPEED), &labelSize);
    CreateWindow(L"static", MY_NAMINGS.SLOW_GENERATION_SPEED, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 250, labelSize.cx, labelSize.cy, hWnd, NULL, wndInstance, NULL);
    GetTextExtentPoint(hdc, MY_NAMINGS.ARRAY_OUTPUT, wcslen(MY_NAMINGS.ARRAY_OUTPUT), &labelSize);
    CreateWindow(L"static", MY_NAMINGS.ARRAY_OUTPUT, WS_CHILD | WS_VISIBLE | WS_TABSTOP, 30, 550, labelSize.cx, labelSize.cy, hWnd, NULL, wndInstance, NULL);
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
}

void createArrayOutput(HWND hWnd, HINSTANCE wndInstance) 
{
    hArrayOutputEdit = CreateWindow(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL, 30, 
                600, 500, 200, hWnd, (HMENU) IDC_ARRAY_OUTPUT, wndInstance, NULL);
}