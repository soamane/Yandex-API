#include "curlrequests.hpp"

curl_slist* CurlRequests::AddHeader(std::string_view first, ...) {
    curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, first.data());

    va_list args;
    va_start(args, first);

    while (const char* header = va_arg(args, const char*)) {
        headers = curl_slist_append(headers, header);
    }

    va_end(args);
    return headers;
}

std::string CurlRequests::PerformHttpRequest(const std::string& url, curl_slist* headers) {
    curl_global_init(CURL_GLOBAL_ALL);

    CURL* curl = nullptr;
    curl = curl_easy_init();
    if (!curl) {
        return std::string();
    }

    if (headers != nullptr) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlRequests::Callback);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        return std::string();
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}

std::size_t CurlRequests::Callback(void* ptr, size_t size, size_t count, std::string* data) {
    data->append(static_cast<char*>(ptr), size * count);
    return size * count;
}
