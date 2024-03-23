#pragma once
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <curl/curl.h>
#include <string>
#include <initializer_list>

/*
    HttpRequest is a utility class for performing HTTP requests using cURL library.
*/
class HttpRequest
{
public:

    /*
        Adds the specified request headers provided as arguments.
        Returns: a pointer to the curl_slist structure.
    */
    static const curl_slist* AddHeaders(std::initializer_list<std::string> headers);

    /*
        Sends a GET request to the specified URL with the provided headers.
        Returns: Server response.
    */
    static const std::string PerformHttpRequest(const std::string& url, const curl_slist* headers);

private:
    /*
        Callback function serving as a handler for HTTP requests.
        Returns: The number of bytes transmitted.
    */
    static std::size_t Callback(void* ptr, size_t size, size_t count, std::string* data);
};

#endif // !HTTP_REQUEST_HPP
