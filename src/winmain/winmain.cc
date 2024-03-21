#include "../gui/gui.hpp"

// 840x500

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    Window window = { };
    WNDCLASSEXW windowClass = window.InitWindowClass();
    HWND hWindow = window.InitWindow();
    
    if (!DirectDevice::CreateDevice(hWindow)) {
        DirectDevice::CleanupDevice();
        window.Destroy();
        return 1;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;      
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);

    bool loop = false;
    while (!loop) {

        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                loop = true;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("123");
        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        DirectDevice::pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    DirectDevice::CleanupDevice();
    window.Destroy();
    return 0;
}