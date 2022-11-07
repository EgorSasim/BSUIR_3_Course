#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>

using namespace std;

#define IDC_TEXTBOX 1000
#define IDC_BUTTON  1001
#define IDC_STATIC  1002

#define MAIN_WINDOW_BACKGOUND_COLOR 1

HWND hMainWindow;
HINSTANCE hMainWindowInstance;

HWND hTextInput;
HWND hButton;
HWND hLabelOutput;

HWND hArrayLengthInput;
HWND hGenerateArrayBtn;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
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
        hTextInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"Type whatever U want here, dude...", WS_VISIBLE | WS_CHILD | ES_LEFT, 50, 50, 380, 25, hWnd, (HMENU)IDC_TEXTBOX, hMainWindowInstance, NULL);
        hButton = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"Generate an array!!!", WS_VISIBLE | WS_CHILD | ES_LEFT, 200, 100, 100, 60, hWnd, HMENU(IDC_BUTTON), hMainWindowInstance, NULL);
        hLabelOutput = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"Some output...", WS_VISIBLE | WS_CHILD | ES_LEFT, 50, 200, 380, 25, hWnd, HMENU(IDC_STATIC), hMainWindowInstance, NULL);
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
            RECT customRect;
            HDC hdc = BeginPaint(hWnd, &ps);
                customRect.top = 10;
                customRect.left = 10;
                customRect.right = 100;
                customRect.bottom = 100;
                DrawTextA(hdc, "RandomText", -1, &customRect, DT_BOTTOM);
            EndPaint(hWnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}