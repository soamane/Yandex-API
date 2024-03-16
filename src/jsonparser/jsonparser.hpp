#pragma once
#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "../api/enums/datatypes.hpp"
#include "../api/structs/factweather.hpp"

#include <vector>
#include <string_view>

#include <rapidjson/document.h>

class Parser
{
public:
	static FactWeather ParseCurrentWeatherData(std::string_view json);
};

#endif // !JSONPARSER_HPP
