#include "api.hpp"
#include "../jsonparser/jsonparser.hpp"
#include "../httprequest/httprequest.hpp"
#include <curl/curl.h>
#include <sstream>

YandexAPI::YandexAPI(std::string_view key) : apiKey(key) { }

const Weather YandexAPI::GetWeather(double latitude, double longitude) {
    const std::string data = RequestGetWeather(latitude, longitude);
    return Parser::ParseWeatherData(data);
}

const std::vector<Forecast> YandexAPI::GetForecast(double latitude, double longitude, unsigned int limit) {
    const std::string data = RequestGetForecast(latitude, longitude, limit);
    return Parser::ParseForecastData(data);
}

const std::string YandexAPI::RequestGetWeather(double latitude, double longitude) {
    std::ostringstream urlStream;
    urlStream << factWeatherUrl << ConvertCoordToURL(latitude, longitude);

    const std::string url = urlStream.str();

    const std::string verifyHeader = GetVerifyHeader();
    const curl_slist* headers = HttpRequest::AddHeaders({ verifyHeader });

    return HttpRequest::PerformHttpRequest(url, headers);
}

const std::string YandexAPI::RequestGetForecast(double latitude, double longitude, unsigned int limit) {
    std::ostringstream urlStream;
    urlStream << forecastWeatherUrl << ConvertCoordToURL(latitude, longitude) << "&limit=" << limit << "&hours=false&extra=false";

    const std::string url = urlStream.str();

    const std::string verifyHeader = GetVerifyHeader();
    const curl_slist* headers = HttpRequest::AddHeaders({ verifyHeader });

    return HttpRequest::PerformHttpRequest(url, headers);
}

const std::string YandexAPI::GetVerifyHeader() {
    return std::string(apiHeader) + std::string(apiKey);
}

const std::string YandexAPI::ConvertCoordToURL(double latitude, double longitude) {
    std::ostringstream coordStream;
    coordStream << "lat=" << latitude << "&lon=" << longitude;

    return coordStream.str();
}
