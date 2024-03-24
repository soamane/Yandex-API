#include "../frontend/ui/wndproc/wndproc.hpp"
#include "../frontend/ui/directdevice/directdevice.hpp"
#include "../frontend/ui/wininfo/wininfo.hpp"

// Function to handle resource cleanup
void CleanupResources(HWND hWindow, WNDCLASSEXW& windowClass) {
    DirectDevice::CleanupDevice();
    DestroyWindow(hWindow);
    UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Class Name", nullptr };
    RegisterClassExW(&wc);
    HWND hwnd = CreateWindowW(wc.lpszClassName, L"Window Name", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, wc.hInstance, nullptr);

    if (!DirectDevice::CreateDevice(hwnd)) {
        DirectDevice::CleanupDevice();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    {
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.IniFilename = nullptr;
    }

    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowPadding = ImVec2{ 0.0f, 0.0f };
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);

    bool done = false;
    while (!done) {

        MSG msg;
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) {
                done = true;
            }
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(WinInfo::size, ImGuiCond_FirstUseEver);
        ImGui::Begin(WinInfo::name.c_str(), &WinInfo::isOpen, WinInfo::flags);
        {
            ImVec2 headerSize = ImVec2{ WinInfo::size.x, WinInfo::size.y * 0.65f };
            ImGui::BeginChild("##header", headerSize, true);
            {

            }
            ImGui::EndChild();

            ImVec2 footerSize = ImVec2{ WinInfo::size.x, WinInfo::size.y * 0.35f };
            ImGui::SetCursorPos(ImVec2{ 0.f, headerSize.y + 1 });
            ImGui::BeginChild("##footer", footerSize, true);
            {
                const int childNum = 7;
                const float offsetForce = 7.0f;
                const float childWidth = (WinInfo::size.x - (childNum - 1) * offsetForce) / childNum;

                for (int i = 0; i < childNum; ++i) {
                    const float offset = i * (childWidth + offsetForce);
                    ImGui::SetCursorPos(ImVec2(offset, 0.f));
                    ImGui::BeginChild(("##day_frame_" + std::to_string(i)).c_str(), ImVec2(childWidth, footerSize.y), true);
                    {

                    }
                    ImGui::EndChild();
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
        ImGui::EndFrame();
        ImGui::Render();

        DirectDevice::pContext->OMSetRenderTargets(1, &DirectDevice::pTargetView, nullptr);
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

    CleanupResources(hwnd, wc);

    return 0;
}
