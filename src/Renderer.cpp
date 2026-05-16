#include "Renderer.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

Renderer::Renderer() {}

Renderer::~Renderer() {
    Cleanup();
}

HRESULT Renderer::Initialize(HWND hwnd) {
    m_hwnd = hwnd;
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
    if (SUCCEEDED(hr)) {
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pWriteFactory));
    }
    if (SUCCEEDED(hr)) {
        hr = m_pWriteFactory->CreateTextFormat(
            L"Segoe UI", NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 14.0f, L"en-us", &m_pTextFormat
        );
    }
    if (SUCCEEDED(hr)) {
        hr = m_pWriteFactory->CreateTextFormat(
            L"Segoe UI", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 10.0f, L"en-us", &m_pSmallTextFormat
        );
    }
    return hr;
}

HRESULT Renderer::CreateDeviceResources() {
    HRESULT hr = S_OK;
    if (!m_pRenderTarget) {
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = m_pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr)) {
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pTextBrush);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.47f, 0.83f, 1.0f), &m_pAccentBrush);
            m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.7f), &m_pBackgroundBrush);
        }
    }
    return hr;
}

void Renderer::DiscardDeviceResources() {
    if (m_pRenderTarget) { m_pRenderTarget->Release(); m_pRenderTarget = nullptr; }
    if (m_pTextBrush) { m_pTextBrush->Release(); m_pTextBrush = nullptr; }
    if (m_pAccentBrush) { m_pAccentBrush->Release(); m_pAccentBrush = nullptr; }
    if (m_pBackgroundBrush) { m_pBackgroundBrush->Release(); m_pBackgroundBrush = nullptr; }
}

void Renderer::Render(const SystemMetrics& metrics) {
    std::cout << "Rendering frame... CPU: " << metrics.cpuUsage << "%" << std::endl;
    if (SUCCEEDED(CreateDeviceResources())) {
        m_pRenderTarget->BeginDraw();
        m_pRenderTarget->Clear(D2D1::ColorF(0, 0));
        D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
        D2D1_ROUNDED_RECT rect = D2D1::RoundedRect(D2D1::RectF(2, 2, rtSize.width - 2, rtSize.height - 2), 8.0f, 8.0f);
        m_pRenderTarget->FillRoundedRectangle(rect, m_pBackgroundBrush);
        
        std::wstringstream ss;
        ss << L"CPU: " << std::fixed << std::setprecision(0) << metrics.cpuUsage << L"%  ";
        ss << L"RAM: " << metrics.ramUsage << L"%  ";
        ss << L"C: " << std::setprecision(1) << metrics.diskCFree << L"GB  ";
        ss << L"D: " << metrics.diskDFree << L"GB";
        
        std::wstring topText = ss.str();
        
        m_pRenderTarget->DrawTextW(
            topText.c_str(), (UINT32)topText.length(), m_pTextFormat,
            D2D1::RectF(15, 5, rtSize.width - 15, rtSize.height / 2), m_pTextBrush
        );

        std::wstringstream ss2;
        ss2 << L"Down: " << std::setprecision(2) << (metrics.netDownload / 1024.0 / 1024.0) << L" MB/s  ";
        ss2 << L"Up: " << (metrics.netUpload / 1024.0 / 1024.0) << L" MB/s";
        
        std::wstring bottomText = ss2.str();
        m_pRenderTarget->DrawTextW(
            bottomText.c_str(), (UINT32)bottomText.length(), m_pSmallTextFormat,
            D2D1::RectF(15, rtSize.height / 2 + 2, rtSize.width - 15, rtSize.height - 5), m_pTextBrush
        );

        m_pRenderTarget->EndDraw();
    }
}

void Renderer::Cleanup() {
    DiscardDeviceResources();
    if (m_pTextFormat) { m_pTextFormat->Release(); m_pTextFormat = nullptr; }
    if (m_pSmallTextFormat) { m_pSmallTextFormat->Release(); m_pSmallTextFormat = nullptr; }
    if (m_pWriteFactory) { m_pWriteFactory->Release(); m_pWriteFactory = nullptr; }
    if (m_pFactory) { m_pFactory->Release(); m_pFactory = nullptr; }
}

void Renderer::Resize(UINT width, UINT height) {
    if (m_pRenderTarget) {
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}
