#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include <format>

#include <string>
#include <string_view>

class YandexAPI
{
public:
	YandexAPI(std::string_view key);

private:
	std::string GetVerifyHeader();
	std::string SetCoordToString(double latitude, double longitude);

private:

	const std::string_view m_key;
	const std::string_view m_header = "X-Yandex-API-Key: ";

	struct APIUrls
	{
		static constexpr std::string_view m_fact = "https://api.weather.yandex.ru/v2/fact?";
		static constexpr std::string_view m_forecast = "https://api.weather.yandex.ru/v2/forecast?";
	};
};

#endif // !YANDEXAPI_HPP
