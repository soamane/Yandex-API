#pragma once
#ifndef FONTS_HPP
#define FONTS_HPP

#include <map>
#include <string>
#include <vector>

#include "../../imgui/imgui.h"

// Class to manage fonts in ImGui
class Fonts
{
public:
    // Initialize source fonts
    void InitSourceFonts();

    // Add font from file
    void AddFontFromFile(const std::string& path, const std::string& name, std::size_t size);

    // Add font from memory
    void AddFontFromMemory(std::vector<unsigned char>& data, const std::string& name, std::size_t size);

    // Get font by name
    ImFont* GetFont(const std::string& name);

private:
    std::map<std::string, ImFont*> fonts; // Map to store loaded fonts
};

#endif // !FONTS_HPP
