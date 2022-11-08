#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>
#include <wingdi.h>

#include "typings.cpp"

using namespace std;

#define IDC_ARRAY_LENGTH        1000
#define IDC_REPETITIONS_AMOUNT  1001
#define IDC_VALUES_RANGE_MIN    1002
#define IDC_VALUES_RANGE_MAX    1003
#define IDC_SLOW_GEN_SPEED      1004
#define IDC_GEN_ARRAY           1005
#define IDC_BUTTON  1010
#define IDC_STATIC  1011


NAMINGS MY_NAMINGS;
GENERATION_PARAMS_STRUCT GENERATION_PARAMS;

HWND hMainWindow;
HINSTANCE hMainWindowInstance;

HWND hTextInput;
HWND hButton;
HWND hLabelOutput;

HWND hArrayLengthInput;
HWND hRepetitionsAmountInput;
HWND hValuesRangeInputMin;
HWND hValuesRangeInputMax;
HWND hSlowGenSpeedInput;

HWND hGenerateArrayBtn;

RECT arrayLengthLb;
RECT repetitionsAmountLb;
RECT valuesRangeLb;
RECT slowGenerationSpeedLb;
RECT generateArrayLb;
RECT writeToFileLb;
RECT valuesTableLb;


void drawLabels(HDC hdc);
void setRectCoords(RECT *rect, LONG top, LONG left, LONG right, LONG bottom);
void generateInputs(HWND hWnd, HINSTANCE wndInstance);
void generateButtons(HWND hWnd, HINSTANCE wndInstance);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    fillNamingsUS(&MY_NAMINGS);
    HBRUSH mainWindowBackgroundColor;
    mainWindowBackgroundColor = CreateSolidBrush(RGB(23, 45, 78));
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
        hMainWindow = hWnd;
        generateInputs(hWnd, hMainWindowInstance);
        generateButtons(hWnd, hMainWindowInstance);
        // hButton = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Generate an array!!!", WS_VISIBLE | WS_CHILD | ES_LEFT, 200, 100, 100, 60, hWnd, HMENU(IDC_BUTTON), hMainWindowInstance, NULL);
        // hLabelOutput = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"Some output...", WS_VISIBLE | WS_CHILD | ES_LEFT, 50, 200, 380, 25, hWnd, HMENU(IDC_STATIC), hMainWindowInstance, NULL);
        break; 
    case WM_COMMAND: 
        if (LOWORD(wParam) == IDC_BUTTON) {
           int textLen = GetWindowTextLength(hTextInput);
           LPSTR pszMem = (LPSTR) VirtualAlloc((LPVOID) NULL, (DWORD)(textLen + 1), MEM_COMMIT, PAGE_READWRITE);
           GetWindowTextA(hTextInput, pszMem, textLen + 1); 
           SetWindowTextA(hLabelOutput, pszMem);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
                drawLabels(hdc);
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

void drawLabels(HDC hdc) 
{  
    HFONT labelsFont, originalFont;
    labelsFont = CreateFontW(40,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
    originalFont = (HFONT)SelectObject(hdc, labelsFont);
    SetTextColor(hdc, RGB(255, 0, 0));

    setRectCoords(&arrayLengthLb, 30, 30, 300, 80);
    setRectCoords(&repetitionsAmountLb, 150, 30, 300, 200);
    setRectCoords(&valuesRangeLb, 270, 30, 300, 355);
    setRectCoords(&slowGenerationSpeedLb, 390, 30, 350, 480);
    DrawTextW(hdc, (LPWSTR)MY_NAMINGS.ARRAY_LENGTH, -1, &arrayLengthLb, DT_BOTTOM);
    DrawTextW(hdc, (LPWSTR)MY_NAMINGS.REPETITIONS_AMOUNT, -1, &repetitionsAmountLb, DT_BOTTOM);
    DrawTextW(hdc, (LPWSTR)MY_NAMINGS.VALUES_RANGE, -1, &valuesRangeLb, DT_BOTTOM);
    DrawTextW(hdc, (LPWSTR)MY_NAMINGS.SLOW_GENERATION_SPEED, -1, &slowGenerationSpeedLb, DT_BOTTOM | DT_WORDBREAK);

    SelectObject(hdc, originalFont);
    DeleteObject(labelsFont);
}

void generateInputs(HWND hWnd, HINSTANCE wndInstance)
{
    hArrayLengthInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 355, 35, 200, 25, hWnd, (HMENU)IDC_ARRAY_LENGTH, wndInstance, NULL);
    hRepetitionsAmountInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 355, 155, 200, 25, hWnd, (HMENU)IDC_REPETITIONS_AMOUNT, wndInstance, NULL);
    hValuesRangeInputMin = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 355, 275, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MIN, wndInstance, NULL);
    hValuesRangeInputMax = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 560, 275, 200, 25, hWnd, (HMENU)IDC_VALUES_RANGE_MAX, wndInstance, NULL);
    hSlowGenSpeedInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"5", WS_VISIBLE | WS_CHILD | ES_LEFT, 355, 395, 200, 25, hWnd, (HMENU)IDC_SLOW_GEN_SPEED, wndInstance, NULL);
}

void generateButtons(HWND hWnd, HINSTANCE wndInstance)
{
    hGenerateArrayBtn = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Generate an array!!!", WS_VISIBLE | WS_CHILD | ES_LEFT, 70, 500, 170, 60, hWnd, HMENU(IDC_GEN_ARRAY), wndInstance, NULL);
}