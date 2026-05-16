#pragma once

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include "Providers.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();

    HRESULT Initialize(HWND hwnd);
    void Render(const SystemMetrics& metrics);
    void Cleanup();
    void Resize(UINT width, UINT height);

private:
    HRESULT CreateDeviceResources();
    void DiscardDeviceResources();

    ID2D1Factory* m_pFactory = nullptr;
    ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
    ID2D1SolidColorBrush* m_pTextBrush = nullptr;
    ID2D1SolidColorBrush* m_pAccentBrush = nullptr;
    ID2D1SolidColorBrush* m_pBackgroundBrush = nullptr;
    IDWriteFactory* m_pWriteFactory = nullptr;
    IDWriteTextFormat* m_pTextFormat = nullptr;
    IDWriteTextFormat* m_pSmallTextFormat = nullptr;

    HWND m_hwnd = NULL;
};
