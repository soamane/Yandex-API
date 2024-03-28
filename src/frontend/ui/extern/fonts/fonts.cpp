#include "fonts.hpp"

#include <windows.h>

void Fonts::InitSourceFonts() {
    for (std::size_t size = 14; size <= 64; size += 2) {
        AddFontFromFile("fonts\\YandexSansText-Regular.ttf", "regular-" + std::to_string(size), size);
        AddFontFromFile("fonts\\YandexSansText-Medium.ttf", "medium-" + std::to_string(size), size);
        AddFontFromFile("fonts\\YandexSansText-Thin.ttf", "thin-" + std::to_string(size), size);
        AddFontFromFile("fonts\\YandexSansText-Light.ttf", "light-" + std::to_string(size), size);
    }
}

void Fonts::AddFontFromFile(const std::string& path, const std::string& name, std::size_t size) {
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(path.c_str(), size, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    if (font) {
        this->fonts[name] = font;
    }
}

void Fonts::AddFontFromMemory(std::vector<unsigned char>& data, const std::string& name, std::size_t size) { 
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromMemoryTTF(data.data(), data.size(), size, nullptr, io.Fonts->GetGlyphRangesCyrillic());
    if (font) {
        this->fonts[name] = font;
    } 
}

ImFont* Fonts::GetFont(const std::string& name) {
    auto it = this->fonts.find(name);
    if (it != this->fonts.end()) {
        return it->second;
    }
    return nullptr;
}
