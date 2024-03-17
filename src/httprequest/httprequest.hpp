#pragma once
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <curl/curl.h>

#include <string>
#include <initializer_list>

class HttpRequest
{
public:
    static const curl_slist* AddHeaders(std::initializer_list<std::string> headers);
    static const std::string PerformHttpRequest(const std::string& url, const curl_slist* headers);

private:
    static std::size_t Callback(void* ptr, size_t size, size_t count, std::string* data);
};

#endif // !HTTP_REQUEST_HPP
