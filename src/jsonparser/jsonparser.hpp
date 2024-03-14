#pragma once
#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "../api/enums/primitives.hpp"
#include "../api/structs/parts/dayparts.hpp"
#include "../api/structs/factweather.hpp"
#include "../api/structs/forecastweather.hpp"

#include <vector>
#include <string_view>

#include <rapidjson/document.h>

class Parser
{
public:
	static FactWeather ParseCurrentWeatherData(std::string_view json);
	static std::vector<ForecastWeather> ParseForecastWeatherData(std::string_view json);
};

#endif // !JSONPARSER_HPP
