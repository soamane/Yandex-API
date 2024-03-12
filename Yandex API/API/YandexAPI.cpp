#include "YandexAPI.hpp"

YandexAPI::YandexAPI(const std::string& key) : api_key(key) { }

std::string YandexAPI::GetVerifyHeader() {
    return std::string(api_header + api_key);
}

std::string YandexAPI::SetCoordToString(double latitude, double longitude) {
    return std::string("lat=" + std::to_string(latitude) + "&lon=" + std::to_string(longitude));
}
