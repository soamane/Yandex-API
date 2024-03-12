#include "YandexAPI.hpp"

YandexAPI::YandexAPI(const std::string& key) : api_key(key) { }

std::string YandexAPI::GetVerifyHeader() {
    return std::string(api_header + api_key);
}
