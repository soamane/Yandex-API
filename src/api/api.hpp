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

	const Weather GetWeather(double latitude, double longitude);
	const std::vector<Forecast> GetForecast(double latitude, double longitude, unsigned int limit);

private:
	const std::string GetVerifyHeader();
	const std::string ConvertCoordToURL(double latitude, double longitude);

	const std::string RequestGetWeather(double latitude, double longitude);
	const std::string RequestGetForecastWeather(double latitude, double longitude, unsigned int limit);

private:
	const std::string_view apiKey;
	const std::string apiHeader = "X-Yandex-API-Key: ";

	const std::string factWeatherUrl = "https://api.weather.yandex.ru/v2/fact?";
	const std::string forecastWeatherUrl = "https://api.weather.yandex.ru/v2/forecast?";
};

#endif // !YANDEXAPI_HPP
