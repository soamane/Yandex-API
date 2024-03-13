#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include "../API/Enums/YandexTypes.hpp"
#include "../API/Structs/Weather/WeatherParts/WeatherParts.hpp"
#include "../API/Structs/Weather/CurrentWeather.hpp"
#include "../API/Structs/Weather/ForecastWeather.hpp"

#include <vector>
#include <string_view>

#include <rapidjson/document.h>

class Parser
{
public:
	static CurrentWeather ParseCurrentWeatherData(std::string_view json);
	static std::vector<ForecastWeather> ParseForecastWeatherData(std::string_view json);
};

#endif // !PARSER_HPP
