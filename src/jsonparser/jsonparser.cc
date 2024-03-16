#include "jsonparser.hpp"

FactWeather Parser::ParseFactWeatherData(std::string_view json) {
	rapidjson::Document document;

	document.Parse(json.data());
	if (!document.IsObject()) {
		return FactWeather();
	}

    FactWeather currentWeather{
            document["temp"].GetInt(),
            document["feels_like"].GetInt(),
            document["pressure_mm"].GetInt(),
            document["pressure_pa"].GetInt(),
            document["humidity"].GetInt(),
            document["prec_prob"].GetBool(),
            document["wind_speed"].GetFloat(),
            document["icon"].GetString(),
            document["condition"].GetString(),
            document["wind_dir"].GetString(),
            document["daytime"].GetString(),
            static_cast<Cloudiness>(document["cloudness"].GetInt()),
            static_cast<PrecType>(document["prec_type"].GetInt()),
            static_cast<PrecStrength>(document["prec_strength"].GetInt())
    };

	return currentWeather;
}