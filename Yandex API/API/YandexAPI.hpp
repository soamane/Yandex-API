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
	std::string api_key = { };
	const std::string api_header = "X-Yandex-API-Key: ";
};

#endif // !YANDEXAPI_HPP
