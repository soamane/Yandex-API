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
	/*
		Parses a JSON-formatted string into a structure of current weather data.
		Accepts a JSON-formatted string as an argument.
		Return value: a populated structure of current weather conditions data.
	*/
	static const Weather ParseWeatherData(std::string_view json);

	/*
		Parses a JSON-formatted string into an array of forecast data.
		Accepts a JSON-formatted string as an argument.
		Return value: an array of weather forecasts.
	*/
	static const std::vector<Forecast> ParseForecastData(std::string_view json);

private:

	/*
		Populates the passed structure with data from corresponding JSON fields.
		Accepts arguments: JSON and a data structure.
	*/
	static void FillWeatherFromJson(const rapidjson::Value& json, Weather& weather);
};

#endif // !JSON_PARSER_HPP
