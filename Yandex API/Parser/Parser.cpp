#include "Parser.hpp"

CurrentWeather Parser::ParseCurrentWeatherData(std::string_view json) {
	rapidjson::Document document;

	document.Parse(json.data());
	if (!document.IsObject()) {
		return CurrentWeather();
	}

	CurrentWeather currentWeather;
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

		auto fillWeatherPart = [&](WeatherPart& part, const rapidjson::Value& jsonPart) {
			part.temp_min = jsonPart["temp_min"].GetInt();
			part.temp_avg = jsonPart["temp_avg"].GetInt();
			part.temp_max = jsonPart["temp_max"].GetInt();
			part.temp_water = jsonPart["temp_water"].GetInt();
			part.feels_like = jsonPart["feels_like"].GetInt();
			part.pressure_mm = jsonPart["pressure_mm"].GetInt();
			part.pressure_pa = jsonPart["pressure_pa"].GetInt();
			part.wind_speed = jsonPart["wind_speed"].GetFloat();
			part.icon = jsonPart["icon"].GetString();
			part.wind_dir = jsonPart["wind_dir"].GetString();
			part.condition = jsonPart["condition"].GetString();
			part.cloudness = static_cast<Cloudiness>(jsonPart["cloudness"].GetInt());
			part.prec_type = static_cast<PrecType>(jsonPart["prec_type"].GetInt());
			part.prec_strength = static_cast<PrecStrength>(jsonPart["prec_strength"].GetInt());
		};

		fillWeatherPart(currentWeather.m_morning, currentForecast["parts"]["morning"]);
		fillWeatherPart(currentWeather.m_day, currentForecast["parts"]["day"]);
		fillWeatherPart(currentWeather.m_night, currentForecast["parts"]["night"]);
	}

	return forecasts;
}
