#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include "structs/weather.hpp"
#include "structs/forecast.hpp"

#include <string>
#include <string_view>

class YandexAPI
{
public:
	YandexAPI(std::string_view key);

	/*
		Receives weather conditions for the current period of time.
		Accepts latitude and longitude coordinates as arguments.
		Return value: structure of weather data.
	*/
	const Weather GetWeather(double latitude, double longitude);

	/*
		Receives an array of forecast data per day.
		Accepts latitude and longitude coordinates as arguments, along with the number of days for forecasting.
		Return value: an array of forecast data per day.
	*/
	const std::vector<Forecast> GetForecast(double latitude, double longitude, unsigned int limit);

private:

	// Returns a ready-made header for request verification.
	const std::string GetVerifyHeader();

	// Converts the coordinates of a point into URL query parameters.
	const std::string ConvertCoordToURL(double latitude, double longitude);

	// Performs a request to obtain current weather conditions in JSON format.
	const std::string RequestGetWeather(double latitude, double longitude);

	// Performs a request to obtain weather forecast conditions in JSON format.
	const std::string RequestGetForecast(double latitude, double longitude, unsigned int limit);

private:
	const std::string_view apiKey; // Individual API key from Yandex.
	const std::string apiHeader = "X-Yandex-API-Key: "; // Name of the Yandex API verification header.

	const std::string factWeatherUrl = "https://api.weather.yandex.ru/v2/fact?"; // URL address for retrieving current weather data
	const std::string forecastWeatherUrl = "https://api.weather.yandex.ru/v2/forecast?"; // URL address for retrieving forecast weather data
};

#endif // !YANDEXAPI_HPP
