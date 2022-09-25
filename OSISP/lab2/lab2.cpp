#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>


LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
    const wchar_t MAIN_CLASS_NAME[] = L"Main class";

    WNDCLASS wCl = {};
    wCl.lpfnWndProc = WindowProc;
    wCl.lpszClassName = MAIN_CLASS_NAME;
    wCl.hCursor = LoadCursor(NULL, IDC_CROSS);

    RegisterClass(&wCl);

    HWND hWnd = CreateWindow(MAIN_CLASS_NAME, L"Main window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, NULL, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while(GetMessage(&msg, hWnd, 0, 0) > 0) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg) 
    {
        case WM_DESTROY: 
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
                FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(0, 255, 0)));
            EndPaint(hWnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}