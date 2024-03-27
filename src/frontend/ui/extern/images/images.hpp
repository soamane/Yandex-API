#pragma once
#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <map>
#include <string>
#include <vector>

#include <d3dx11.h>

#include "../../imgui/imgui.h"
#include "../../platform/directdevice/directdevice.hpp"

// Class to manage images in ImGui
class Images
{
public:
    // Initialize source icons
    void InitSourceIcons();

    // Add image from file
    void AddImageFromFile(const std::string& path, const std::string& name);

    // Add image from memory
    void AddImageFromMemory(std::vector<unsigned char>& data, const std::string& name);

    // Get image by name
    ID3D11ShaderResourceView* GetImage(const std::string& image);

private:
    std::map<std::string, ID3D11ShaderResourceView*> images; // Map to store loaded images
};

#endif // !IMAGES_HPP
