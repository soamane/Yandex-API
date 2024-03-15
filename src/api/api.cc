#include "api.hpp"

YandexAPI::YandexAPI(std::string_view key) : m_key(key) { }

FactWeather YandexAPI::GetFactWeather(double latitude, double longitude) {
    const std::string data = RequestGetFactWeather(latitude, longitude);
    return Parser::ParseCurrentWeatherData(data);
}

std::vector<ForecastWeather> YandexAPI::GetForecastWeather(double latitude, double longitude, int limit) {
    const std::string data = RequestGetForecastWeather(latitude, longitude, limit);
    return Parser::ParseForecastWeatherData(data);
}

std::string YandexAPI::RequestGetFactWeather(double latitude, double longitude) {
    const std::string coords = SetCoordToString(latitude, longitude);
    const std::string url = std::format("{}{}", m_fact, coords);

    const std::string verifyHeader = GetVerifyHeader();
    curl_slist* headers = CurlRequests::AddHeader(verifyHeader);

    return CurlRequests::PerformHttpRequest(url, headers);
}

std::string YandexAPI::RequestGetForecastWeather(double latitude, double longitude, unsigned int limit) {
    const std::string coords = SetCoordToString(latitude, longitude);
    const std::string url = std::format("{}{}&limit={}&hours=false&extra=false", m_forecast, coords, limit);

    const std::string verifyHeader = GetVerifyHeader();
    curl_slist* headers = CurlRequests::AddHeader(verifyHeader);

    return CurlRequests::PerformHttpRequest(url, headers);
}

std::string YandexAPI::GetVerifyHeader() {
    return std::format("{}{}", m_header, m_key);
}

std::string YandexAPI::SetCoordToString(double latitude, double longitude) {
    return std::format("lat={}&lon={}", latitude, longitude);
}
