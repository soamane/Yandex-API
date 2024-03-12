#include "YandexAPI.hpp"

YandexAPI::YandexAPI(std::string_view key) : m_key(key) { }

std::string YandexAPI::GetCurrentWeather(double latitude, double longitude) {
    const std::string coords = SetCoordToString(latitude, longitude);
    const std::string url = std::format("{}{}", m_fact, coords);

    curl_slist* headers = { nullptr };
    const std::string header = GetVerifyHeader();
    headers = curl_slist_append(headers, header.c_str());

    return Requests::PerformHttpRequest(url, headers);
}

std::string YandexAPI::GetForecastWeather(double latitude, double longitude, unsigned int limit) {
    const std::string coords = SetCoordToString(latitude, longitude);
    const std::string url = std::format("{}{}&limit={}&hours=false&extra=false", m_forecast, coords, limit);

    curl_slist* headers = { nullptr };
    const std::string header = GetVerifyHeader();
    headers = curl_slist_append(headers, header.c_str());

    return Requests::PerformHttpRequest(url, headers);
}

std::string YandexAPI::GetVerifyHeader() {
    return std::format("{}{}", m_header, m_key);
}

std::string YandexAPI::SetCoordToString(double latitude, double longitude) {
    return std::format("lat={}&lon={}", latitude, longitude);
}
