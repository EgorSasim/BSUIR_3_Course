#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


#include <stdio.h>

int TABLE_ROW_NUM = 5;
int TABLE_COL_NUM = 5;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void DrawTable(HWND hWnd, HDC hdc, int rowsNum, int colNum);
 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR args, int nCmdShow)
{
    const wchar_t MAIN_CLASS_NAME[] = L"Main class";
    
    WNDCLASS wCl = {};
    MSG msg;
    HWND hWnd;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    int argc;
    LPWSTR *argList = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argc == 1) 
    {
        MessageBox(NULL, L"No parameters was passed\nDefault parameters will be used(5x5)", L"Tooltip", MB_OK);
    } else 
    {
       TABLE_ROW_NUM = atoi((char*)argList[1]);
       TABLE_COL_NUM = atoi((char*)argList[2]);
       printf("%dx%d", TABLE_ROW_NUM, TABLE_COL_NUM);
    }
    LocalFree(argList);
   

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

   
    wCl.lpfnWndProc = WindowProc;
    wCl.lpszClassName = MAIN_CLASS_NAME;
    wCl.hCursor = LoadCursor(NULL, IDC_CROSS);
    wCl.hInstance = hInstance;
    wCl.style =  CS_HREDRAW | CS_VREDRAW; 

    RegisterClass(&wCl);

    hWnd = CreateWindow(MAIN_CLASS_NAME, L"Main window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, NULL, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    
    while(GetMessage(&msg, hWnd, 0, 0) > 0) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg) 
    {
        case WM_KEYDOWN: 
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
            }
            return 0;
        }
        case WM_DESTROY: 
        {
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
                FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(234, 12, 76)));
                DrawTable(hWnd, hdc, TABLE_ROW_NUM, TABLE_COL_NUM);
            EndPaint(hWnd, &ps);
            return 0;
        }

    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void DrawTable(HWND hWnd, HDC hdc, int rowNum, int colNum)
{
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
    RECT windRect;
    int windWidth;
    int windHeight;
    int rowSize;
    int colSize;

    GetWindowRect(hWnd, &windRect);
    printf("Window size: %dx%d\n", windRect.right - windRect.left, windRect.bottom - windRect.top);
    windHeight = windRect.bottom - windRect.top;
    windWidth = windRect.right - windRect.left;

    rowSize = windHeight / rowNum;
    colSize = windWidth / colNum;
    
    //Draw rows
    for (int i = 0; i < rowNum; ++i) 
    {
        graphics.DrawLine(&pen, 0, i * rowSize, windWidth, i * rowSize);
    }
    
    //Draw colums
    for (int i = 0; i < colNum; ++i)
    {
        graphics.DrawLine(&pen, i * colSize, 0, i * colSize, windHeight);
    }
}