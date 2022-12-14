#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <string>

using namespace std;

#define H_KEY 0x48
#define J_KEY 0x4A
#define K_KEY 0x4B
#define L_KEY 0x4C

int rectTopLeftX = 50;
int rectTopLeftY = 50;
int rectBottomRightX = 150;
int rectBottomRightY = 150;
 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    
    // Register the window class.
    const wchar_t MAIN_NAME[]  = L"Main Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = MAIN_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RegisterClass(&wc);


    HWND hwndMain = CreateWindowEx(
        0,                              // Optional window styles.
        MAIN_NAME,                     // Window class
        L"Rectangle movement",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwndMain == NULL)
    {
        return 0;
    }

    ShowWindow(hwndMain, nCmdShow);


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
    //    TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT mWinRect;

    switch (uMsg)
    {
        case WM_DESTROY:
            MessageBox(hwnd, L"Have a good day)", L"Goodbye", MB_OK | MB_ICONINFORMATION);
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_ESCAPE:
                PostQuitMessage(0);
                break;
            case VK_RIGHT:
                rectTopLeftX += 10;
                rectBottomRightX += 10;   
                break;
            case VK_LEFT:
                rectTopLeftX -= 10;
                rectBottomRightX -= 10;   
                break;
            case VK_UP:
                rectTopLeftY -= 10;
                rectBottomRightY -= 10;   
                break;
            case VK_DOWN:
                rectTopLeftY += 10;
                rectBottomRightY += 10;   
                break;
            case H_KEY: 
                rectTopLeftX -= 10;
                rectBottomRightX -= 10;   
		        break;
            case J_KEY: 
                rectTopLeftY += 10;
                rectBottomRightY += 10;   
		        break;
            case K_KEY: 
                rectTopLeftY -= 10;
                rectBottomRightY -= 10;   
		        break;
            case L_KEY: 
                rectTopLeftX += 10;
                rectBottomRightX += 10;   
		        break;
            default:
                break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_LBUTTONDOWN: 
            if (wParam & MK_SHIFT) 
            {
                rectTopLeftY -= 10;
                rectBottomRightY -= 10;   
            }
            else 
            {
                rectTopLeftX -= 10;
                rectBottomRightX -= 10;   
            }
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_RBUTTONDOWN: 
            if (wParam & MK_SHIFT) 
            {
                rectTopLeftY += 10;
                rectBottomRightY += 10;   
            }
            else 
            {
                rectTopLeftX += 10;
                rectBottomRightX += 10;   
            }
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        case WM_MOUSEWHEEL: 
        {
            int wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (wheelDelta > 0) 
            {
                if (wParam & MK_SHIFT) 
                {
                    rectTopLeftX -= 10;
                    rectBottomRightX -= 10; 
                }
                else 
                {
                    rectTopLeftY -= 10;
                    rectBottomRightY -= 10;  
                }
            } 
            else 
            {
                if (wParam & MK_SHIFT) 
                {
                    rectTopLeftX += 10;
                    rectBottomRightX += 10; 
                }
                else 
                {
                    rectTopLeftY += 10;
                    rectBottomRightY += 10; 
                }
            }
            InvalidateRect(hwnd, NULL, TRUE);
            return 0;
        }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            GetWindowRect(hwnd, &mWinRect);
            int mWWidth = mWinRect.right - mWinRect.left;
            int mWHeight = mWinRect.bottom - mWinRect.top;

            HDC hdc = BeginPaint(hwnd, &ps);

                HPEN newPen = CreatePen(PS_SOLID, 5, RGB(0,0, 255));
                HBRUSH newBrush = CreateSolidBrush(RGB(255,255,0));

                HGDIOBJ oldPen = SelectObject(hdc, newPen);
                HGDIOBJ oldBrush = SelectObject(hdc, newBrush);



 
                if (rectTopLeftX <= 0 || rectTopLeftY <= 0 || rectBottomRightX >= mWWidth || rectBottomRightY >= mWHeight)
                {
                    rectTopLeftX = 50;
                    rectTopLeftY = 50;
                    rectBottomRightX = 150;
                    rectBottomRightY = 150;     
                }
                              
                
                Rectangle(hdc, rectTopLeftX, rectTopLeftY, rectBottomRightX, rectBottomRightY);

                SelectObject(hdc, oldBrush);
                SelectObject(hdc, oldPen);
                DeleteObject(newPen);
                DeleteObject(newBrush);

            EndPaint(hwnd, &ps);
        }
        return 0;
        case WM_CLOSE: 
        {
            if (MessageBox(hwnd, L"Do you really want to quit?", L"My application", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
            {
                DestroyWindow(hwnd);
            }
            return 0;
        }

    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
