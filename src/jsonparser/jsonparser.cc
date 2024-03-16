#include "jsonparser.hpp"

FactWeather Parser::ParseCurrentWeatherData(std::string_view json) {
	rapidjson::Document document;

	document.Parse(json.data());
	if (!document.IsObject()) {
		return FactWeather();
	}

	FactWeather currentWeather;
	currentWeather.temp = document["temp"].GetInt();
	currentWeather.feels_like = document["feels_like"].GetInt();
	currentWeather.pressure_mm = document["pressure_mm"].GetInt();
	currentWeather.pressure_pa = document["pressure_pa"].GetInt();
	currentWeather.humidity = document["humidity"].GetInt();

	currentWeather.prec_prob = document["prec_prob"].GetBool();

	currentWeather.wind_speed = document["wind_speed"].GetFloat();

	currentWeather.icon = document["icon"].GetString();
	currentWeather.condition = document["condition"].GetString();
	currentWeather.wind_dir = document["wind_dir"].GetString();
	currentWeather.daytime = document["daytime"].GetString();

	currentWeather.cloudness = static_cast<Cloudiness>(document["cloudness"].GetInt());
	currentWeather.prec_type = static_cast<PrecType>(document["prec_type"].GetInt());
	currentWeather.prec_strength = static_cast<PrecStrength>(document["prec_strength"].GetInt());

	return currentWeather;
}