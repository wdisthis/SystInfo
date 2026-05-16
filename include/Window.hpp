#pragma once
#include "Providers.hpp"
#include "Renderer.hpp"

class MainWindow {
public:
    MainWindow();
    ~MainWindow();

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

    HWND Window() const { return m_hwnd; }

protected:
    virtual PCWSTR ClassName() const { return L"SystInfoWindowClass"; }
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd = NULL;
    Renderer m_renderer;
    SystemProviders m_providers;
};
