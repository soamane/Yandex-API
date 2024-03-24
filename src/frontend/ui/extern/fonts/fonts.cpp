#include "fonts.hpp"

void Fonts::AddFontFromFile(const std::string& path, const std::string& name, std::size_t size) { 
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(path.c_str(), size);
    if (font) {
        this->fonts[name] = font;
    }
}

void Fonts::AddFontFromMemory(std::vector<unsigned char>& data, const std::string& name, std::size_t size) { 
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromMemoryTTF(data.data(), data.size(), size);
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
