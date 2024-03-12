#pragma once
#ifndef REQUESTS_HPP
#define REQUESTS_HPP

#include <curl/curl.h>
#include <string>

class Requests
{
public:
	static std::string PerformHttpRequest(const std::string& url, curl_slist* headers);

private:
	static std::size_t Callback(void* ptr, size_t size, size_t count, std::string* data);
};

#endif // !REQUESTS_HPP
