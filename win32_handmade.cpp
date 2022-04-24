#include "Windows.h"

LRESULT CALLBACK MainWindowCallback(
  HWND Window,
  UINT Message,
  WPARAM wParam,
  LPARAM lParam
)
{
  LRESULT Result = 0;
  switch (Message) {
    case WM_SIZE:
    {
      OutputDebugString("Size\n");
    }
    break;
    case WM_DESTROY:
    {
      OutputDebugString("Destroy\n");
    }
    break;
    case WM_CLOSE:
    {
      OutputDebugString("Close\n");
    }
    break;
    case WM_ACTIVATEAPP:
    {
      OutputDebugString("Activate\n");
    }
    break;
    case WM_PAINT:
    {
      OutputDebugString("Activate\n");
      PAINTSTRUCT Paint;
      HDC DeviceContext = BeginPaint(Window, &Paint);
      int X = Paint.rcPaint.left;
      int Y = Paint.rcPaint.top;
      int Width = Paint.rcPaint.right - X;
      int Height = Paint.rcPaint.bottom - Y;
      static DWORD Operation = WHITENESS;

      PatBlt(DeviceContext, X, Y, Width, Height, Operation);

      if (Operation == WHITENESS) {
        Operation = BLACKNESS;
      } else {
        Operation = WHITENESS;
      }
      
      EndPaint(Window, &Paint);
    }
    break;
    default:
    {
      Result = DefWindowProc(Window, Message, wParam, lParam);
    }
  }
  return Result;
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE ignored, PWSTR CmdLineArgs, int StartupMode) {
  WNDCLASSA WindowClass = {};
  WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = Instance;
  WindowClass.lpszClassName = "HandmadeHeroWindowClass";

  if (RegisterClassA(&WindowClass)) {
    HWND WindowHandle = CreateWindowExA(
      0,
      WindowClass.lpszClassName,
      "Handmade Hero",
      WS_OVERLAPPEDWINDOW|WS_VISIBLE,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      0,
      0,
      Instance,
      0
    );
    if (WindowHandle) {
      MSG Message;
      for(;;) {
        BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
        if (MessageResult > 0) {
          TranslateMessage(&Message);
          DispatchMessage(&Message);
        } else {
          break;
        }
      }
    } else {
      OutputDebugString("CreateWindowExA failed!");
    }
  } else {
    OutputDebugString("RegisterClassA failed!");
  }
  
  return 0;
}