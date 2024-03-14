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

std::vector<ForecastWeather> Parser::ParseForecastWeatherData(std::string_view json) {
	rapidjson::Document document;

	document.Parse(json.data());
	if (!document.IsObject()) {
		return std::vector<ForecastWeather>();
	}

	rapidjson::Value& forecastArray = document["forecasts"];
	rapidjson::SizeType forecastCount = forecastArray.Size();

	std::vector<ForecastWeather> forecasts(forecastCount);

	for (rapidjson::SizeType i = 0; i < forecastCount; ++i) {
		rapidjson::Value& currentForecast = forecastArray[i];
		ForecastWeather& currentWeather = forecasts[i];

		currentWeather.m_date = currentForecast["date"].GetString();

		auto fillWeatherPart = [&](WeatherPart& part, const rapidjson::Value& arg) {
			part.temp_min = arg["temp_min"].GetInt();
			part.temp_avg = arg["temp_avg"].GetInt();
			part.temp_max = arg["temp_max"].GetInt();
			part.temp_water = arg["temp_water"].GetInt();
			part.feels_like = arg["feels_like"].GetInt();
			part.pressure_mm = arg["pressure_mm"].GetInt();
			part.pressure_pa = arg["pressure_pa"].GetInt();
			part.wind_speed = arg["wind_speed"].GetFloat();
			part.icon = arg["icon"].GetString();
			part.wind_dir = arg["wind_dir"].GetString();
			part.condition = arg["condition"].GetString();
			part.cloudness = static_cast<Cloudiness>(arg["cloudness"].GetInt());
			part.prec_type = static_cast<PrecType>(arg["prec_type"].GetInt());
			part.prec_strength = static_cast<PrecStrength>(arg["prec_strength"].GetInt());
		};

		fillWeatherPart(currentWeather.m_morning, currentForecast["parts"]["morning"]);
		fillWeatherPart(currentWeather.m_day, currentForecast["parts"]["day"]);
		fillWeatherPart(currentWeather.m_night, currentForecast["parts"]["night"]);
	}

	return forecasts;
}
