#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include <string>

class YandexAPI
{
public:
	YandexAPI(const std::string& key);

private:
	std::string GetVerifyHeader();
	std::string SetCoordToString(double latitude, double longitude);

private:

	const std::string m_key = { };
	const std::string m_header = "X-Yandex-API-Key: ";

	struct URL
	{
		static const inline std::string fact = "https://api.weather.yandex.ru/v2/fact?";
		static const inline std::string forecast = "https://api.weather.yandex.ru/v2/forecast?";
	};
};

#endif // !YANDEXAPI_HPP
