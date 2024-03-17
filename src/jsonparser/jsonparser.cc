#include "jsonparser.hpp"

FactWeather Parser::ParseFactWeatherData(std::string_view json) {
    rapidjson::Document document;

    document.Parse(json.data());
    if (!document.IsObject()) {
        return FactWeather();
    }

    FactWeather currentWeather;
    FillWeatherFromJson(document, currentWeather);

    return currentWeather;
}

std::vector<ForecastWeather> Parser::ParseForecastWeatherData(std::string_view json) {
    rapidjson::Document document;

    document.Parse(json.data());
    if (!document.IsObject()) {
        return std::vector<ForecastWeather>();
    }

    const rapidjson::Value& forecasts = document["forecasts"];
    if (!forecasts.IsArray()) {
        return std::vector<ForecastWeather>();
    }

    std::vector<ForecastWeather> resultForecast;
    resultForecast.resize(forecasts.Size());

    for (const auto& forecast : forecasts.GetArray()) {
        ForecastWeather forecastWeather;
        forecastWeather.m_date = forecast["date"].GetString();

        FillWeatherFromJson(forecast["parts"]["morning"], forecastWeather.m_morning);
        FillWeatherFromJson(forecast["parts"]["day"], forecastWeather.m_day);
        FillWeatherFromJson(forecast["parts"]["evening"], forecastWeather.m_evening);
        FillWeatherFromJson(forecast["parts"]["night"], forecastWeather.m_night);

        resultForecast.push_back(std::move(forecastWeather));
    }

    return resultForecast;
}

void Parser::FillWeatherFromJson(const rapidjson::Value& json, FactWeather& weather) {
    json.HasMember("temp_avg") ? weather.temp = json["temp_avg"].GetInt() : weather.temp = json["temp"].GetInt();
    weather.feels_like = json["feels_like"].GetInt();
    weather.wind_speed = json["wind_speed"].GetDouble();
    weather.pressure_mm = json["pressure_mm"].GetInt();
    weather.pressure_pa = json["pressure_pa"].GetInt();
    weather.humidity = json["humidity"].GetInt();
    weather.prec_prob = json["prec_prob"].GetBool();
    weather.icon = json["icon"].GetString();
    weather.wind_dir = json["wind_dir"].GetString();
    weather.condition = json["condition"].GetString();
    weather.daytime = json["daytime"].GetString();
    weather.cloudness = static_cast<Cloudiness>(json["cloudness"].GetInt());
    weather.prec_type = static_cast<PrecType>(json["prec_type"].GetInt());
    weather.prec_strength = static_cast<PrecStrength>(json["prec_strength"].GetInt());
}
