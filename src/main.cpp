#include "Window.hpp"
#include <shellapi.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    MainWindow win;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int width = 450;
    int height = 50;
    int x = screenWidth - width - 10;
    int y = screenHeight - height - 50;

    if (!win.Create(L"SystInfo Widget", WS_POPUP, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW, x, y, width, height)) {
        return 0;
    }

    ShowWindow(win.Window(), nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
