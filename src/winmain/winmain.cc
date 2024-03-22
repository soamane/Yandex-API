#include "../ui/directdevice/directdevice.hpp"
#include "../ui/ui.hpp"

// Function to handle resource cleanup
void CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass) {
    DirectDevice::CleanupDevice();
    DestroyWindow(hWindow);
    UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize window class
    WNDCLASSEXW windowClass = { };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_CLASSDC;
    windowClass.lpfnWndProc = WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.hIcon = nullptr;
    windowClass.hCursor = nullptr;
    windowClass.hbrBackground = nullptr;
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = L"YANDEXAPI";
    windowClass.hIconSm = nullptr;

    // Register window class
    if (!RegisterClassExW(&windowClass)) {
        MessageBox(nullptr, "Failed to register window class", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Create window
    HWND hWindow = CreateWindowW(windowClass.lpszClassName, L"Yandex API", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, windowClass.hInstance, nullptr);
    if (hWindow == nullptr) {
        MessageBox(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
        return 1;
    }

    // Initialize DirectDevice
    if (!DirectDevice::CreateDevice(hWindow)) {
        MessageBox(nullptr, "Failed to initialize DirectDevice", "Error", MB_OK | MB_ICONERROR);
        CleanupResources(hWindow, windowClass);
        return 1;
    }

    // Initialize ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    // Configure ImGui style
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.WindowPadding = ImVec2(0, 0);
        style.WindowBorderSize = 0.f;
        style.ChildBorderSize = 1.f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui::StyleColorsLight();

    // Initialize ImGui Win32 and DirectX11 bindings
    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);

    // Main loop
    bool loop = false;
    while (!loop) {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                loop = true;
            }
        }

        // ImGui frame setup
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Your ImGui code goes here...

        ImGui::EndFrame();
        ImGui::Render();

        // Render ImGui draw data
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        // Update and render ImGui platform windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // Present the frame
        DirectDevice::pSwapChain->Present(1, 0);
    }

    // Cleanup resources
    CleanupResources(hWindow, windowClass);

    // Destroy ImGui context
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
