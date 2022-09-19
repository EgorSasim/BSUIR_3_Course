#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <windowsx.h>
#include <winnt.h>
#pragma comment(lib, "Msimg32.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void paintWind(HWND hwnd);
void mvrght(HWND hwnd);
void mvlft(HWND hwnd);
void mvup(HWND hwnd);
void mvdwn(HWND hwnd);
void mvPctr(HWND hwnd);

HINSTANCE h;
CONST INT TRNSPCLR = 0xFF00FF, ELA = 140, ELB = 60;
int x = 150, y = 300, dx = 10, dy = 10, ela = 140, elb = 60, col = 80, mdx = 10, sgndx = 1, sgndy = 1, kol = 0, x2, y2;
HBITMAP gBM;
boolean onPict = false, onMove = false, mvx = false, mvy = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
  h = hInstance;
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = { };

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hbrBackground = (HBRUSH)(3);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  RegisterClass(&wc);

  // Create the window.

  HWND hwnd = CreateWindowEx(
    0,                              // Optional window styles.
    CLASS_NAME,                     // Window class
    L"SuperFigure",          // Window text
    WS_OVERLAPPEDWINDOW,            // Window style

    // Size and position
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

    NULL,       // Parent window    
    NULL,       // Menu
    hInstance,  // Instance handle
    NULL        // Additional application data
  );

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);

  // Run the message loop.

  MSG msg = { };

  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

int rrr = 8;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);

  switch (uMsg)
  {
  case WM_CLOSE:
  {
    if (MessageBox(hwnd, L"Really quit?", L"Super application", MB_OKCANCEL) == IDOK)
    {
      DestroyWindow(hwnd);
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
    paintWind(hwnd);
    return 0;
  }

  case WM_CREATE:
  {
    HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"penguin.cpp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    gBM = hBmp;
    break;
  }

  case WM_ERASEBKGND:
  {
    return 1;
  }

  case WM_MOUSEMOVE:
  {
    if (onMove)
      return 0;

    x = GET_X_LPARAM(lParam) - (ela) / 2;
    y = GET_Y_LPARAM(lParam) - (elb) / 2;
    x2 = x + ela;
    y2 = y + elb;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x2 > clientRect.right) x = clientRect.right - ela;
    if (y2 > clientRect.bottom) y = clientRect.bottom - elb;
    InvalidateRect(hwnd, &clientRect, true);
    return 0;
  }

  case WM_MOUSEWHEEL:
  {
    if (onMove)
      return 0;

    int key = GET_KEYSTATE_WPARAM(wParam);
    if (key == MK_SHIFT)
    {
      mvx = true;
      mvy = false;
      if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        sgndx = -1;
      else
        sgndx = 1;
    }
    else
    {
      mvy = true;
      mvx = false;
      if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
        sgndy = -1;
      else
        sgndy = 1;
    }

    mvPctr(hwnd);
    mvx = false;
    mvy = false;
    return 0;
  }

  case WM_KEYDOWN:
  {
    if (wParam != VK_TAB)
      if (onMove)
        return 0;

    switch (wParam)
    {
    case VK_RIGHT:
      mvrght(hwnd);
      break;

    case VK_LEFT:
      mvlft(hwnd);
      break;

    case VK_UP:
      mvup(hwnd);
      break;

    case VK_DOWN:
      mvdwn(hwnd);
      break;

    case VK_TAB:
      if (!onPict)
      {
        onPict = true;
        BITMAP bm;
        GetObject(gBM, sizeof(bm), &bm);
        ela = bm.bmWidth;
        elb = bm.bmHeight;
        InvalidateRect(hwnd, &clientRect, true);
        mvrght(hwnd);
        mvdwn(hwnd);
      }
      else
      {
        onPict = false;
        ela = ELA;
        elb = ELB;
      }
      break;
    }
    break;
    return 0;
  }


  ///////////////////////////////////////////////



  case WM_LBUTTONDOWN:
  {
    if ((abs(GET_X_LPARAM(lParam) - (x + ela / 2)) > 40)  || (abs(GET_Y_LPARAM(lParam) - (y + elb/2)) > 40))
        break;
    
    if (!(mvx || mvy))
    {
      mdx = 0;
      onMove = true;
      rrr = SetTimer(hwnd, 0, 37, (TIMERPROC)NULL);
    }

    kol += 1;
    rrr = !mvx * mvy;
    mvx = true;

    if (mvy)
      mvy = false;
    else
    {
      mvx = false;
      mvy = true;
    }
    mdx += 1;
    return 0;
  }

  case WM_TIMER:
  {
    mvPctr(hwnd);
    return 0;
  }
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void mvrght(HWND hwnd)
{
  x += mdx;
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  if (x + ela > clientRect.right)
  {
    sgndx *= -1;
    x = clientRect.right - ela;
  }
  InvalidateRect(hwnd, &clientRect, true);
  return;
}

void mvdwn(HWND hwnd)
{
  y += mdx;
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  if (y + elb > clientRect.bottom)
  {
    y = clientRect.bottom - elb;
    sgndy *= -1;
  }
  InvalidateRect(hwnd, &clientRect, true);
  return;
}

void mvlft(HWND hwnd)
{
  x -= mdx;
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  if (x < 0)
  {
    sgndx *= -1;
    x = 0;
  }
  InvalidateRect(hwnd, &clientRect, true);
  return;
}

void mvup(HWND hwnd)
{
  y -= mdx;
  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  if (y < 0)
  {
    sgndy *= -1;
    y = 0;
  }
  InvalidateRect(hwnd, &clientRect, true);
  return;
}

void mvPctr(HWND hwnd)
{
  if (mvx)
    if (sgndx == 1)
      mvrght(hwnd);
    else
      mvlft(hwnd);
  else
    if (sgndy == 1)
      mvdwn(hwnd);
    else
      mvup(hwnd);
}

void paintWind(HWND hwnd)
{
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(hwnd, &ps);

  RECT clientRect;
  GetClientRect(hwnd, &clientRect);
  HBITMAP hbmBack = CreateCompatibleBitmap(hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
  HDC backDc = CreateCompatibleDC(hdc);
  HGDIOBJ previousBackBmp = SelectObject(backDc, hbmBack);
  FillRect(backDc, &clientRect, (HBRUSH)(3));

  if (onPict == false)
  {
    HBRUSH hBrush;
    hBrush = CreateSolidBrush(RGB(0, 0, col));
    HGDIOBJ oldBrush = SelectObject(backDc, hBrush);
    Ellipse(backDc, x, y, x + ela, y + elb);
    SelectObject(backDc, oldBrush);
  }
  else
  {
    //DWORD error = GetLastError();
    HDC pict = CreateCompatibleDC(hdc);
    HGDIOBJ previousBmp = SelectObject(pict, gBM);

    BITMAP bm;
    GetObject(gBM, sizeof(bm), &bm);
    ela = bm.bmWidth;
    elb = bm.bmHeight;

    // TransparentBlt(backDc, x, y, bm.bmWidth, bm.bmHeight, pict, 0, 0, bm.bmWidth, bm.bmHeight, TRNSPCLR);
    SelectObject(pict, previousBmp);//? is it needed in case of the next line?    
    ReleaseDC(hwnd, pict);
  }

  wchar_t text[] = L"0123456789";
  int c1, c2, c3;
  wchar_t tc1[] = L"0\0", tc2[] = L"1\0", tc3[] = L"2\0";
  c1 = kol % 1000 / 100;
  c2 = kol % 100 / 10;
  c3 = kol % 10;
  tc1[0] = text[c1];
  tc2[0] = text[c2];
  tc3[0] = text[c3];
  SetBkColor(backDc, RGB(0x64, 0x95, 0xED));

  int k = TextOut(backDc, 0, 0, L"caught: ", ARRAYSIZE(L"caught: "));
  k = TextOut(backDc, 56, 0, tc1, ARRAYSIZE(tc1));
  k = TextOut(backDc, 64, 0, tc2, ARRAYSIZE(tc2));
  k = TextOut(backDc, 72, 0, tc3, ARRAYSIZE(tc3));

  BitBlt(hdc, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, backDc, 0, 0, SRCCOPY);
  SelectObject(backDc, previousBackBmp);//?
  DeleteDC(backDc);
  EndPaint(hwnd, &ps);
}