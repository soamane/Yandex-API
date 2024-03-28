#pragma once
#ifndef WIN_INFO_HPP
#define WIN_INFO_HPP

#include <string>

#include "../../imgui/imgui.h"

// Structure to hold window information
struct WinInfo
{
    static inline bool isOpen = true;
    static const inline std::string name = "##main"; 
    static const inline ImVec2 size = { 700.f, 530.f }; 
    static const inline ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
};

#endif // !WIN_INFO_HPP
