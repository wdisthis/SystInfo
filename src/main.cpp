#include "Window.hpp"
#include <shellapi.h>
#include <iostream>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    MainWindow win;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int width = 450;
    int height = 50;
    int x = screenWidth - width - 10;
    int y = screenHeight - height - 50;

    std::cout << "Creating window..." << std::endl;
    if (!win.Create(L"SystInfo Widget", WS_POPUP, WS_EX_TOPMOST, x, y, width, height)) {
        std::cerr << "Failed to create window!" << std::endl;
        MessageBoxW(NULL, L"Failed to create window or initialize Direct2D", L"Error", MB_ICONERROR);
        return 0;
    }
    std::cout << "Window created successfully." << std::endl;

    std::cout << "Showing window with nCmdShow: " << nCmdShow << std::endl;
    ShowWindow(win.Window(), nCmdShow);

    std::cout << "Starting message loop..." << std::endl;
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    std::cout << "Message loop finished with msg: " << msg.message << std::endl;

    return 0;
}
