#pragma once
#ifndef YANDEXAPI_HPP
#define YANDEXAPI_HPP

#include <string>

class YandexAPI
{
public:
	YandexAPI(const std::string& key);

protected:
	std::string GetVerifyHeader();

private:
	std::string api_key = { };
	const std::string api_header = "X-Yandex-API-Key: ";
};

#endif // !YANDEXAPI_HPP
