#pragma once
#ifndef FONTS_HPP
#define FONTS_HPP

#include <map>
#include <string>
#include <vector>

#include "../../imgui/imgui.h"

class Fonts
{
public:
	void AddFontFromFile(const std::string& path, const std::string& name, std::size_t size);
	void AddFontFromMemory(std::vector<unsigned char>& data, const std::string& name, std::size_t size);

	ImFont* GetFont(const std::string& name);
private:
	std::map<std::string, ImFont*> fonts;
};

#endif // !FONTS_HPP
