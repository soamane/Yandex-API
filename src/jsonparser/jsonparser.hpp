#pragma once
#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "../api/datatypes/datatypes.hpp"
#include "../api/structs/weather.hpp"
#include "../api/structs/forecast.hpp"

#include <vector>
#include <string_view>

#include <rapidjson/document.h>

class Parser
{
public:
	static const Weather ParseWeatherData(std::string_view json);
	static const std::vector<Forecast> ParseForecastData(std::string_view json);

private:
	static void FillWeatherFromJson(const rapidjson::Value& json, Weather& weather);
};

#endif // !JSON_PARSER_HPP
