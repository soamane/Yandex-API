#include "window.hpp"

WNDCLASSEXW Window::InitWindowClass() {
    this->windowClass.cbSize = sizeof(WNDCLASSEX);
    this->windowClass.style = CS_CLASSDC;
    this->windowClass.lpfnWndProc = WndProc;
    this->windowClass.cbClsExtra = 0;
    this->windowClass.cbWndExtra = 0;
    this->windowClass.hInstance = GetModuleHandle(nullptr);
    this->windowClass.hIcon = nullptr;
    this->windowClass.hCursor = nullptr;
    this->windowClass.hbrBackground = nullptr;
    this->windowClass.lpszMenuName = nullptr;
    this->windowClass.lpszClassName = L"YANDEXAPI";
    this->windowClass.hIconSm = nullptr;

    RegisterClassExW(&windowClass);
    return windowClass;
}

HWND Window::InitWindow() {
    this->hwnd = CreateWindowW(windowClass.lpszClassName, L"Yandex API", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, windowClass.hInstance, nullptr);
    return hwnd;
}

void Window::Destroy() { 
    DestroyWindow(this->hwnd);
    UnregisterClassW(this->windowClass.lpszClassName, this->windowClass.hInstance);
}
