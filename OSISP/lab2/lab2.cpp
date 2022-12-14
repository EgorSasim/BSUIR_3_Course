#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <stdio.h>


int TABLE_ROW_NUM = 5;
int TABLE_COL_NUM = 5;
RECT *CELLS_ARR;

std::stringstream FILE_TEXT;
std::vector<std::string> CELLS_TEXT;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
void DrawTable(HWND hWnd, HDC hdc, int rowsNum, int colNum);
void WriteTextToTable(HDC hdc, std::vector<std::string> cellsText, int ccText, RECT *tableCells, UINT format, int rowsNum, int colsNums);
RECT *CreateTableCells(int rowsNum, int colsNum);
void SetTableCellsProps(HWND hwnd, HDC hdc, RECT *tableCells, int rowsNum, int colsNum);
void DrawTableCelss(HDC hdc, RECT *tableCells, COLORREF penCol, COLORREF brushCol, int rowsNum, int colsNum);
void CheckTableCellsProps(RECT *tableCells, int rowsNum, int colsNum);
void ReadFileText(std::string fileName);
void GetTableCellsText(std::string text, int rowsNum, int colsNum);

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

    CELLS_ARR = CreateTableCells(TABLE_ROW_NUM, TABLE_COL_NUM);
    ReadFileText("textFile.txt");
    GetTableCellsText(FILE_TEXT.str(), TABLE_ROW_NUM, TABLE_COL_NUM);

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
    free(CELLS_ARR);
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
            RECT rcWindow;
            RECT rc1 = rcWindow;
            rc1.left = 0;
            rc1.right = 200;
            rc1.top = 0;
            rc1.bottom = 200;
            GetClientRect(hWnd, &rcWindow);
            HDC hdc = BeginPaint(hWnd, &ps);
                FillRect(hdc, &ps.rcPaint, CreateSolidBrush(RGB(234, 12, 76)));
                // DrawTable(hWnd, hdc, TABLE_ROW_NUM, TABLE_COL_NUM);
                SetTableCellsProps(hWnd, hdc, CELLS_ARR, TABLE_ROW_NUM, TABLE_COL_NUM);
                DrawTableCelss(hdc, CELLS_ARR, RGB(0,255,0), RGB(0, 0, 255), TABLE_ROW_NUM, TABLE_COL_NUM);
                WriteTextToTable(hdc, CELLS_TEXT, -1, CELLS_ARR, DT_CENTER | DT_WORDBREAK, TABLE_ROW_NUM, TABLE_COL_NUM);
                // CheckTableCellsProps(CELLS_ARR, TABLE_ROW_NUM, TABLE_COL_NUM);
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

void WriteTextToTable(HDC hdc, std::vector<std::string> cellsText, int ccText, RECT *tableCells, UINT format, int rowsNum, int colsNum)
{
    SetBkMode(hdc, TRANSPARENT);
    SetBkColor(hdc, RGB(0, 0, 0));
    for (int i = 0; i < rowsNum * colsNum; ++i)
    {
        DrawTextA(hdc, cellsText[i].c_str(), ccText, &tableCells[i], format);
    }
}

RECT *CreateTableCells(int rowsNum, int colsNum)
{
    int cellsNum = rowsNum * colsNum;
    RECT *cellsArr;
    cellsArr = (RECT *)malloc(sizeof(RECT) * cellsNum );
    if (cellsArr == NULL) 
    {
        MessageBox(NULL, L"Array of cells was not created", L"Warning!!!", MB_ICONSTOP);
    }
    return cellsArr;
}

void DrawTableCelss(HDC hdc, RECT *tableCells, COLORREF penCol, COLORREF brushCol, int rowsNum, int colsNum)
{
    HPEN hpen = CreatePen(PS_SOLID, 2, penCol);
    HBRUSH hBrush = CreateSolidBrush(brushCol);

    SelectObject(hdc, hpen);
    SelectObject(hdc, hBrush);

    for (int i = 0; i < rowsNum * colsNum; ++i)
    {
        Rectangle(hdc, tableCells[i].left, tableCells[i].top, tableCells[i].right, tableCells[i].bottom);
    }
}

void SetTableCellsProps(HWND hwnd, HDC hdc, RECT *tableCells, int rowsNum, int colsNum)
{
    RECT rcWindow;
    GetClientRect(hwnd, &rcWindow);
    int windowWidth;
    int windowHeight;
    int rowSize;
    int colSize;

    windowWidth = rcWindow.right - rcWindow.left;
    windowHeight = rcWindow.bottom - rcWindow.top;

    rowSize = windowWidth / colsNum;
    colSize = windowHeight / rowsNum;
    
    int i = 0;
    for (int row = 0; row < rowsNum; ++row)
    {
        for (int col = 0; col < colsNum; ++col)
        {
            tableCells[i].top = row * colSize;
            tableCells[i].left = col * rowSize;
            tableCells[i].bottom = row * colSize + colSize;
            tableCells[i].right = col * rowSize + rowSize;
            ++i;
        }
    }
}

void CheckTableCellsProps(RECT *tableCells, int rowsNum, int colsNum)
{
    for (int i = 0; i < rowsNum * colsNum; ++i)
    {
        printf("left: %d, top: %d, right: %d, bottom: %d\n", tableCells[i].left, tableCells[i].top, tableCells[i].right, tableCells[i].bottom);
    }
}

void ReadFileText(std::string fileName)
{
    std::ifstream inpFile(fileName);
    FILE_TEXT << inpFile.rdbuf();
}

void GetTableCellsText(std::string text, int rowsNum, int colsNum)
{
    int cellsNum = rowsNum * colsNum;
    int oneCellTextLength = text.length() / cellsNum;

    int anchor = 0;
    for (int i = 0; i < cellsNum; ++i) 
    {
        CELLS_TEXT.push_back(text.substr(anchor, oneCellTextLength));
        anchor += oneCellTextLength;
    }

    std:: cout << "Vector val: \n";
    for (std::string i: CELLS_TEXT)
    {
        std::cout << i << "\n";
    }

}