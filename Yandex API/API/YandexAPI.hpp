#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include "../Requests/Requests.hpp"

#include <curl/curl.h>

#include <format>

#include <string>
#include <string_view>

class YandexAPI
{
public:
	YandexAPI(std::string_view key);
	std::string RequestGetCurrentWeather(double latitude, double longitude);
	std::string RequestGetForecastWeather(double latitude, double longitude, unsigned int limit);

private:
	std::string GetVerifyHeader();
	std::string SetCoordToString(double latitude, double longitude);

private:
	const std::string_view m_key;
	const std::string_view m_header = "X-Yandex-API-Key: ";

	const std::string_view m_fact = "https://api.weather.yandex.ru/v2/fact?";
	const std::string_view m_forecast = "https://api.weather.yandex.ru/v2/forecast?";
};

#endif // !YANDEXAPI_HPP
