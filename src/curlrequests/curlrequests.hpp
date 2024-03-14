#pragma once
#ifndef CURLREQUEST_HPP
#define CURLREQUEST_HPP

#include <curl/curl.h>
#include <string>

class CurlRequests
{
public:
	static curl_slist* AddHeader(std::string_view header, ...);
	static std::string PerformHttpRequest(const std::string& url, curl_slist* headers);

private:
	static std::size_t Callback(void* ptr, size_t size, size_t count, std::string* data);
};

#endif // !CURLREQUEST_HPP
