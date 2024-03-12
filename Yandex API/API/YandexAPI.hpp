#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include <string_view>
#include <format>

class YandexAPI
{
public:
	YandexAPI(const std::string& key);

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
