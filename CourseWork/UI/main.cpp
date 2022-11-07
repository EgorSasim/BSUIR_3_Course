#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>

#include "typings.cpp"

using namespace std;

#define IDC_TEXTBOX 1000
#define IDC_BUTTON  1001
#define IDC_STATIC  1002

#define MAIN_WINDOW_BACKGOUND_COLOR 1

NAMINGS MY_NAMINGS;

HWND hMainWindow;
HINSTANCE hMainWindowInstance;

HWND hTextInput;
HWND hButton;
HWND hLabelOutput;

 char* ARRAY_LENGTH = "Array length: ";
    char* REPETITIONS_AMOUNT = "Repetitions count: ";
    char* VALUES_RANGE = "Values range: ";
    char* SLOW_GENERATION_SPEED = "Slow generation speed by \'n\' times: ";
    char* GENERATE_ARRAY = "Generate array";
    char* WRITE_TO_FILE = "Write to file";
    char* VALUES_TABLE = "Values table";

HWND hArrayLengthInput;
HWND hGenerateArrayBtn;

RECT arrayLengthLb;
RECT repetitionsAmountLb;
RECT valuesRangeLb;
RECT slowGenerationSpeedLb;
RECT generateArrayLb;
RECT writeToFileLb;
RECT valuesTableLb;

int drawLabels(HDC hdc);
void setRectCoords(RECT *rect, LONG top, LONG left, LONG right, LONG bottom);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    fillNamingsUS(&MY_NAMINGS);
    const wchar_t MAIN_WINDOW_CLASS_NAME[]  = L"Main Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = MAIN_WINDOW_CLASS_NAME;
    wc.hbrBackground = (HBRUSH)MAIN_WINDOW_BACKGOUND_COLOR;

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
        // hTextInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Type whatever U want here, dude...", WS_VISIBLE | WS_CHILD | ES_LEFT, 50, 50, 380, 25, hWnd, (HMENU)IDC_TEXTBOX, hMainWindowInstance, NULL);
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

int drawLabels(HDC hdc) 
{  
    setRectCoords(&arrayLengthLb, 10, 10, 100, 50);
    setRectCoords(&repetitionsAmountLb, 70, 10, 100, 80);
    setRectCoords(&valuesRangeLb, 90, 10, 100, 110);
    setRectCoords(&slowGenerationSpeedLb, 130, 10, 100, 150);
    DrawTextA(hdc, (LPCSTR)MY_NAMINGS.ARRAY_LENGTH, -1, &arrayLengthLb, DT_BOTTOM);
    DrawTextA(hdc, (LPCSTR)MY_NAMINGS.REPETITIONS_AMOUNT, -1, &repetitionsAmountLb, DT_BOTTOM);
    DrawTextA(hdc, (LPCSTR)MY_NAMINGS.VALUES_RANGE, -1, &valuesRangeLb, DT_BOTTOM);
    DrawTextA(hdc, (LPCSTR)MY_NAMINGS.SLOW_GENERATION_SPEED, -1, &slowGenerationSpeedLb, DT_BOTTOM);
}