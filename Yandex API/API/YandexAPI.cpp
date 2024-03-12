#include "YandexAPI.hpp"

YandexAPI::YandexAPI(std::string_view key) : m_key(key) { }

std::string YandexAPI::GetVerifyHeader() {
    return std::string(m_header) + std::string(m_key);
}

std::string YandexAPI::SetCoordToString(double latitude, double longitude) {
    return std::string("lat=") + std::to_string(latitude) + std::string("&lon=") + std::to_string(longitude);
}
