#include "../frontend/ui/render/render.hpp"

#include "../frontend/ui/platform/wndproc/wndproc.hpp"
#include "../frontend/ui/platform/window/window.hpp"

// Entry point of the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // Parse CmdLine
    std::string cmdLine = std::string(lpCmdLine);

    size_t pos1 = cmdLine.find_first_of(' ');
    if (pos1 == std::string::npos) {
        MessageBoxA(nullptr, "Usage: <token> <latitude> <longitude>", nullptr, MB_ICONERROR | MB_OK);
        return -1;
    }

    std::string token = cmdLine.substr(0, pos1);
    size_t pos2 = cmdLine.find_first_of(' ', pos1 + 1);
    if (pos2 == std::string::npos) {
        MessageBoxA(0, "Usage: <token> <latitude> <longitude>", nullptr, MB_ICONERROR | MB_OK);
        return -1;
    }

    std::string lat = cmdLine.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string lon = cmdLine.substr(pos2 + 1);
    if (lat.empty() || lon.empty()) {
        MessageBoxA(nullptr, "Usage: <token> <latitude> <longitude>", nullptr, MB_ICONERROR | MB_OK);
        return -1;
    }
     
    // Initializing the window
    WNDCLASSEXW wc = { };
    HWND hwnd = nullptr;

    Window::Init(wc, hwnd);

    // Creating the Direct3D device
    if (!DirectDevice::CreateDevice(hwnd)) {
        Window::CleanupResources(hwnd, wc);
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    {
        // Configuring ImGui flags
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.IniFilename = nullptr;
    }

    // Configuring ImGui style
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

    // Initializing fonts
    Fonts fonts;
    fonts.InitSourceFonts();

    // Initializing images
    Images images;
    images.InitSourceIcons();

    // Initializing ImGui Win32 and DirectX 11 bindings
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(DirectDevice::pDevice, DirectDevice::pContext);
    {
        // Initializing YandexAPI and retrieving weather data
        YandexAPI api = YandexAPI(token);
        const Weather fact = api.GetWeather(std::stoi(lat), std::stoi(lon));
        const std::vector<Forecast> forecast = api.GetForecast(std::stoi(lat), std::stoi(lon));

        // Initializing rendering
        Render::Init(images, fonts, fact, forecast);
    }

    // Shutting down ImGui Win32 and DirectX 11 bindings
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // Cleaning up resources
    Window::CleanupResources(hwnd, wc);
    return 0;
}
