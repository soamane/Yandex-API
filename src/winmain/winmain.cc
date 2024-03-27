#include "../frontend/ui/render/render.hpp"

#include "../frontend/ui/platform/wndproc/wndproc.hpp"
#include "../frontend/ui/platform/window/window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEXW wc = { };
    HWND hwnd = nullptr;
    
    Window window;
    window.Init(wc, hwnd);

    if (!DirectDevice::CreateDevice(hwnd)) {
        window.CleanupResources(hwnd, wc);
        return 1;
    }

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
        style.FramePadding = ImVec2{ 0.0f, 0.0f };
        style.ItemSpacing = ImVec2{ 0.0f, 0.0f };
        style.ItemInnerSpacing = ImVec2{ 0.0f,0.0f };
        style.TouchExtraPadding = ImVec2{ 0.0f, 0.0f };
        style.IndentSpacing = 0;
        style.ScrollbarSize = 0;
        style.GrabMinSize = 0;
        style.FrameBorderSize = 0.f;
        style.FrameRounding = 7.f;
    }

    Fonts fonts;
    fonts.InitSourceFonts();

    Images images;
    images.InitSourceIcons();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);
    {
        YandexAPI api = YandexAPI("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
        const Weather fact = api.GetWeather(56.8597, 35.9119);
        const std::vector<Forecast> forecast = api.GetForecast(56.8597, 35.9119);

        Render::Init(images, fonts, fact, forecast);
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    window.CleanupResources(hwnd, wc);
    return 0;
}
