#pragma once
#ifndef IMAGES_HPP
#define IMAGES_HPP

#include <map>
#include <string>
#include <vector>

#include <d3dx11.h>

#include "../../imgui/imgui.h"
#include "../../platform/directdevice/directdevice.hpp"

class Images
{
public:
	void AddImageFromFile(const std::string& path, const std::string& name);
	void AddImageFromMemory(std::vector<unsigned char>& data, const std::string& name);

	ID3D11ShaderResourceView* GetImage(const std::string& image);
private:
	std::map<std::string, ID3D11ShaderResourceView*> images;
};

#endif // !IMAGES_HPP
