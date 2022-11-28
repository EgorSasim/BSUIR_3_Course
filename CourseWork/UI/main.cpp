#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <wingdi.h>

#include "../Typings/typings.cpp"
// #include "../Core/cntrep.cpp"

using namespace std;

#define IDC_ARRAY_LENGTH        1000
#define IDC_REPETITIONS_AMOUNT  1001
#define IDC_VALUES_RANGE_MIN    1002
#define IDC_VALUES_RANGE_MAX    1003
#define IDC_SLOW_GEN_SPEED      1004
#define IDC_GEN_ARRAY           1005
#define IDC_BUTTON  1010
#define IDC_STATIC  1011


#define INPUT_MAX_LENGTH 25

NAMINGS MY_NAMINGS;
GENERATION_PARAMS_STRUCT GENERATION_PARAMS;

HWND hMainWindow;
HINSTANCE hMainWindowInstance;

HWND hTextInput;
HWND hButton;
HWND hLabelOutput;



// Label controls
HWND hArrayLengthLb;
HWND hRepetitionsAmountLb;
HWND hValuesRangeLb;
HWND hSlowGenerationSpeedLb;
HWND hGenerateArrayLb;
HWND hWriteToFileLb;
HWND hValuesTableLb;

// Input controls
HWND hArrayLengthInput;
HWND hRepetitionsAmountInput;
HWND hValuesRangeInputMin;
HWND hValuesRangeInputMax;
HWND hSlowGenSpeedInput;

//Buton controls
HWND hGenerateArrayBtn;
HWND hWriteToFileBtn;


void setRectCoords(RECT *rect, LONG top, LONG left, LONG right, LONG bottom);
void createControls(HWND hWnd, HINSTANCE wndInstance);
void createLabels(HWND hWnd, HINSTANCE wndInstance, HDC hdc) ;
void createInputs(HWND hWnd, HINSTANCE wndInstance);
void createButtons(HWND hWnd, HINSTANCE wndInstance);
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

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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
        hMainWindow = hWnd;
        createControls(hWnd, hMainWindowInstance);
        createInputs(hWnd, hMainWindowInstance);
        createButtons(hWnd, hMainWindowInstance);
        // hButton = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Generate an array!!!", WS_VISIBLE | WS_CHILD | ES_LEFT, 200, 100, 100, 60, hWnd, HMENU(IDC_BUTTON), hMainWindowInstance, NULL);
        // hLabelOutput = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"Some output...", WS_VISIBLE | WS_CHILD | ES_LEFT, 50, 200, 380, 25, hWnd, HMENU(IDC_STATIC), hMainWindowInstance, NULL);
        break; 
    }  
    case WM_COMMAND: 
        if (LOWORD(wParam) == IDC_GEN_ARRAY) {
            wchar_t* arrayLength;
            wchar_t* repetitionsAmount;
            wchar_t* valueRangeMin;
            wchar_t* valueRangeMax;
            wchar_t* slowGenSpeed;
            GetWindowText(hArrayLengthInput, arrayLength, INPUT_MAX_LENGTH);
            GetWindowText(hRepetitionsAmountInput, repetitionsAmount, INPUT_MAX_LENGTH);
            GetWindowText(hValuesRangeInputMin, valueRangeMin, INPUT_MAX_LENGTH);
            GetWindowText(hValuesRangeInputMax, valueRangeMax, INPUT_MAX_LENGTH);
            GetWindowText(hArrayLengthInput, slowGenSpeed, INPUT_MAX_LENGTH);

            ERRORS_ENUM errs = checkErrors(arrayLength, repetitionsAmount, valueRangeMin, valueRangeMax, slowGenSpeed);

            if (errs == VALID) 
            {
                printf("AMAZING!!!");
            }

        // printf("Array length: %s %d", &arrayLength, _wtoi(&arrayLength));
        //    int textLen = GetWindowTextLength(hTextInput);
        //    LPSTR pszMem = (LPSTR) VirtualAlloc((LPVOID) NULL, (DWORD)(textLen + 1), MEM_COMMIT, PAGE_READWRITE);
        //    GetWindowTextA(hTextInput, pszMem, textLen + 1); 
        //    SetWindowTextA(hLabelOutput, pszMem);
        }
        break;
    case WM_DESTROY:
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

void createControls(HWND hWnd, HINSTANCE wndInstance) 
{
        return;
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
}

void createInputs(HWND hWnd, HINSTANCE wndInstance)
{
    hArrayLengthInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 50, 200, 25, hWnd, (HMENU)IDC_ARRAY_LENGTH, wndInstance, NULL);
    hRepetitionsAmountInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 120, 200, 25, hWnd, (HMENU)IDC_REPETITIONS_AMOUNT, wndInstance, NULL);
    hValuesRangeInputMin = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 190, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MIN, wndInstance, NULL);
    hValuesRangeInputMax = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 250, 190, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MAX, wndInstance, NULL);
    hSlowGenSpeedInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 270, 200, 25, hWnd, (HMENU)IDC_SLOW_GEN_SPEED, wndInstance, NULL);
}

void createButtons(HWND hWnd, HINSTANCE wndInstance)
{
    hGenerateArrayBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", MY_NAMINGS.GENERATE_ARRAY, WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 350, 500, 60, hWnd, HMENU(IDC_GEN_ARRAY), wndInstance, NULL);
    hWriteToFileBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", MY_NAMINGS.WRITE_TO_FILE, WS_VISIBLE | WS_CHILD | ES_LEFT, 30, 450, 500, 60, hWnd, HMENU(IDC_GEN_ARRAY), wndInstance, NULL);
}