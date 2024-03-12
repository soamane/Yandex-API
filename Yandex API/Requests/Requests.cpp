#include "Requests.hpp"

std::string Requests::PerformHttpRequest(const std::string& url, curl_slist* headers) {
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Requests::Callback);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        return std::string();
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}

std::size_t Requests::Callback(void* ptr, size_t size, size_t count, std::string* data) {
    data->append(static_cast<char*>(ptr), size * count);
    return size * count;
}
