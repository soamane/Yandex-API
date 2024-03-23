#include "httprequest.hpp"

#include <stdexcept>

const curl_slist* HttpRequest::AddHeaders(std::initializer_list<std::string> headers) {
    curl_slist* headerList = nullptr;
    for (const auto& header : headers) {
        headerList = curl_slist_append(headerList, header.c_str());
        if (!headerList) {
            throw std::runtime_error("Failed to add headers");
        }
    }
    return headerList;
}

const std::string HttpRequest::PerformHttpRequest(const std::string& url, const curl_slist* headers) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("Failed to perform HTTP request");
    }

    return response;
}

std::size_t HttpRequest::Callback(void* ptr, size_t size, size_t count, std::string* data) {
    data->append(static_cast<char*>(ptr), size * count);
    return size * count;
}
