#pragma once
#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include "../api/enums/datatypes.hpp"
#include "../api/structs/weather.hpp"
#include "../api/structs/forecastweather.hpp"

#include <vector>
#include <string_view>

#include <rapidjson/document.h>

class Parser
{
public:
	static Weather ParseWeatherData(std::string_view json);
	static std::vector<ForecastWeather> ParseForecastWeatherData(std::string_view json);

private:
	static void FillWeatherFromJson(const rapidjson::Value& json, Weather& weather);
};

#endif // !JSONPARSER_HPP
