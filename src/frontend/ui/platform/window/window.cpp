#include "window.hpp"

#include "../wndproc/wndproc.hpp"
#include "../directdevice/directdevice.hpp"

void Window::Init(WNDCLASSEXW& wc, HWND& hwnd) {
    wc = 
    { 
        sizeof(wc), 
        CS_CLASSDC,
        WndProc, 
        0L, 
        0L, 
        GetModuleHandle(nullptr), 
        nullptr,
        nullptr, 
        nullptr, 
        nullptr, 
        L"Class Name", 
        nullptr 
    };

    RegisterClassExW(&wc);
    hwnd = CreateWindowW(wc.lpszClassName, L"Window Name", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, wc.hInstance, nullptr);
}

void Window::CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass) { 
    DirectDevice::CleanupDevice();
    DestroyWindow(hWindow);
    UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
}
