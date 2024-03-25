#include "../backend/jsonparser/jsonparser.hpp"
#include "../backend/api/api.hpp"

#include "../frontend/ui/platform/wndproc/wndproc.hpp"
#include "../frontend/ui/platform/directdevice/directdevice.hpp"
#include "../frontend/ui/platform/wininfo/wininfo.hpp"

#include "../frontend/ui/extern/fonts/fonts.hpp"
#include "../frontend/ui/extern/images/images.hpp"

#include <sstream>

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
        style.WindowPadding = ImVec2(0, 0);
        style.FramePadding = ImVec2(0, 0);
        style.ItemSpacing = ImVec2(0, 0);
        style.ItemInnerSpacing = ImVec2(0, 0);
        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 0;
        style.ScrollbarSize = 0;
        style.GrabMinSize = 0;
        style.FrameBorderSize = 0.f;
    }

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);

    Fonts fonts;
    fonts.InitSourceFonts();

    Images images;
    images.InitSourceIcons();

    YandexAPI api = YandexAPI("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
    auto fact = api.GetWeather(56.8597, 35.9119);
    auto forecast = api.GetForecast(56.8597, 35.9119, 7);

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
            const ImVec2 headerSize = ImVec2{ WinInfo::size.x, WinInfo::size.y * 0.65f };
            ImGui::BeginChild("##header", headerSize, true);
            {      
                fact.daytime == "n" ? ImGui::Image(images.GetImage("n_bg"), headerSize) : ImGui::Image(images.GetImage("d_bg"), headerSize);

                ImGui::PushFont(fonts.GetFont("regular-64"));
                {
                    std::string title = "Tver " + std::to_string(fact.temp) + u8"°";
                    ImVec2 titleSize = ImGui::CalcTextSize(title.c_str());
                    ImVec2 titlePos = ImVec2{ (headerSize.x - titleSize.x) / 2.0f, (headerSize.y - titleSize.y) / 2.0f };
                    ImGui::SetCursorPos(titlePos);
                    ImGui::TextColored(ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f }, title.c_str());
                }   
                ImGui::PopFont();

                ImGui::PushFont(fonts.GetFont("regular-26"));
                {
                    std::ostringstream stream;
                    stream.precision(1);
                    stream << std::fixed << fact.wind_speed; 

                    std::string description = "Now " + fact.condition + ", wind " + stream.str() + " m/s";
                    ImVec2 descriptionSize = ImGui::CalcTextSize(description.c_str());
                    ImVec2 descriptionPos = ImVec2{ (headerSize.x - descriptionSize.x) / 2.0f, (headerSize.y - descriptionSize.y) / 1.5f };

                    ImGui::SetCursorPos(descriptionPos);
                    ImGui::TextColored(ImVec4{ 1.0f, 1.0f, 1.0f, 0.7f }, description.c_str());
                }
                ImGui::PopFont();
            }
            ImGui::EndChild();

            const ImVec2 footerSize = ImVec2{ WinInfo::size.x, WinInfo::size.y * 0.35f };
            ImGui::SetCursorPos(ImVec2{ 0.f, headerSize.y + 1 });
            ImGui::BeginChild("##footer", footerSize, true);
            {
                const int childNum = 7;
                const int offsetNum = childNum - 1;
                const float offsetForce = 7.0f;
                const float childWidth = (WinInfo::size.x - offsetNum * offsetForce) / childNum;

                for (int i = 0; i < childNum; ++i) {
                    const float offset = i * (childWidth + offsetForce);
                    ImGui::SetCursorPos(ImVec2(offset, 0.f));
                    ImGui::BeginChild(("##day_frame_" + std::to_string(i)).c_str(), ImVec2(childWidth, footerSize.y), true);
                    {
                        float offsetY = 10.0f;
                        ImVec2 childPos = ImGui::GetItemRectMin();
                        if (ImGui::IsMouseHoveringRect(childPos, ImVec2(childPos.x + childWidth, childPos.y + footerSize.y))) {
                            offsetY -= 5.0f;
                        }

                        std::string date = forecast[i].date;
                        {                          
                            ImVec2 dateSize = ImGui::CalcTextSize(date.c_str());
                            ImVec2 datePos = ImVec2{ (childWidth - dateSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(datePos);
                            ImGui::TextColored(ImVec4{ 0.0f, 0.0f, 0.f, 0.3f }, forecast[i].date.c_str(), i + 20);
                            offsetY += dateSize.y + 5.0f; 
                        }

                        std::string dayTemp = std::to_string(forecast[i].day.temp) + u8"° on day";
                        {                           
                            ImVec2 dayTempSize = ImGui::CalcTextSize(dayTemp.c_str());
                            ImVec2 dayTempPos = ImVec2{ (childWidth - dayTempSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(dayTempPos);
                            ImGui::Text(dayTemp.c_str());
                            offsetY += dayTempSize.y + 5.0f;
                        }

                        std::string eveningTemp = std::to_string(forecast[i].evening.temp) + u8"° on evening";
                        {
                            ImVec2 eveningTempSize = ImGui::CalcTextSize(eveningTemp.c_str());
                            ImVec2 eveningTempPos = ImVec2{ (childWidth - eveningTempSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(eveningTempPos);
                            ImGui::TextColored(ImVec4{ 0.0f, 0.0f, 0.f, 0.3f }, eveningTemp.c_str());
                            offsetY += eveningTempSize.y + 5.0f;
                        }

                        std::string nightTemp = std::to_string(forecast[i].night.temp) + u8"° on night";
                        {
                            ImVec2 nightTempSize = ImGui::CalcTextSize(nightTemp.c_str());
                            ImVec2 nightTempPos = ImVec2{ (childWidth - nightTempSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(nightTempPos);
                            ImGui::TextColored(ImVec4{ 0.0f, 0.0f, 0.f, 0.3f }, nightTemp.c_str());
                            offsetY += nightTempSize.y + 5.0f; 
                        }

                        auto icon = images.GetImage(forecast[i].day.icon.c_str());
                        {
                            ImVec2 iconSize = ImVec2{ 32, 32 };
                            ImVec2 iconPos = ImVec2{ (childWidth - iconSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(iconPos);
                            ImGui::Image(icon, iconSize);
                            offsetY += iconSize.y + 5.0f; 
                        }

                        std::string condition = forecast[i].day.condition;
                        {                         
                            ImVec2 conditionSize = ImGui::CalcTextSize(condition.c_str());
                            ImVec2 conditionPos = ImVec2{ (childWidth - conditionSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(conditionPos);
                            ImGui::TextColored(ImVec4{ 0.0f, 0.0f, 0.f, 0.3f }, condition.c_str());
                            offsetY += conditionSize.y + 5.0f; 
                        }

                        std::string feels = std::to_string(forecast[i].day.feels_like) + u8"° feels like";
                        {
                            ImVec2 feelsSize = ImGui::CalcTextSize(feels.c_str());
                            ImVec2 feelsPos = ImVec2{ (childWidth - feelsSize.x) / 2.0f, offsetY };
                            ImGui::SetCursorPos(feelsPos);
                            ImGui::TextColored(ImVec4{ 0.0f, 0.0f, 0.f, 0.3f }, feels.c_str());
                            offsetY += feelsPos.y + 5.0f;
                        }                       
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
