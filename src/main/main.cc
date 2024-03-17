#include "../api/api.hpp"

#include <iostream>

int main() {
	YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
	std::vector<ForecastWeather> forecasts = api.GetForecastWeather(12.345, 65.435, 1);

    for (auto forecast : forecasts) {
        std::cout << "Date: " << forecast.m_date << std::endl;

        // Утро
        std::cout << "Morning:" << std::endl;
        std::cout << "\tTemperature: " << forecast.m_morning.temp << std::endl;
        std::cout << "\tFeels Like: " << forecast.m_morning.feels_like << std::endl;
        std::cout << "\tWind Speed: " << forecast.m_morning.wind_speed << std::endl;
        std::cout << "\tWind Direction: " << forecast.m_morning.wind_dir << std::endl;
        std::cout << "\tPressure (mm): " << forecast.m_morning.pressure_mm << std::endl;
        std::cout << "\tPressure (pa): " << forecast.m_morning.pressure_pa << std::endl;
        std::cout << "\tHumidity: " << forecast.m_morning.humidity << std::endl;
        std::cout << "\tPrecipitation Probability: " << forecast.m_morning.prec_prob << std::endl;
        std::cout << "\tPrecipitation Type: " << forecast.m_morning.prec_type << std::endl;
        std::cout << "\tPrecipitation Strength: " << forecast.m_morning.prec_strength << std::endl;
        std::cout << "\tDaytime: " << forecast.m_morning.daytime << std::endl;
        std::cout << "\tCondition: " << forecast.m_morning.condition << std::endl;
        std::cout << "\tCloudiness: " << forecast.m_morning.cloudness << std::endl;
        std::cout << "\tIcon: " << forecast.m_morning.icon << std::endl;

        // День
        std::cout << "Day:" << std::endl;
        std::cout << "\tTemperature: " << forecast.m_day.temp << std::endl;
        std::cout << "\tFeels Like: " << forecast.m_day.feels_like << std::endl;
        std::cout << "\tWind Speed: " << forecast.m_day.wind_speed << std::endl;
        std::cout << "\tWind Direction: " << forecast.m_day.wind_dir << std::endl;
        std::cout << "\tPressure (mm): " << forecast.m_day.pressure_mm << std::endl;
        std::cout << "\tPressure (pa): " << forecast.m_day.pressure_pa << std::endl;
        std::cout << "\tHumidity: " << forecast.m_day.humidity << std::endl;
        std::cout << "\tPrecipitation Probability: " << forecast.m_day.prec_prob << std::endl;
        std::cout << "\tPrecipitation Type: " << forecast.m_day.prec_type << std::endl;
        std::cout << "\tPrecipitation Strength: " << forecast.m_day.prec_strength << std::endl;
        std::cout << "\tDaytime: " << forecast.m_day.daytime << std::endl;
        std::cout << "\tCondition: " << forecast.m_day.condition << std::endl;
        std::cout << "\tCloudiness: " << forecast.m_day.cloudness << std::endl;
        std::cout << "\tIcon: " << forecast.m_day.icon << std::endl;

        // Вечер
        std::cout << "Evening:" << std::endl;
        std::cout << "\tTemperature: " << forecast.m_evening.temp << std::endl;
        std::cout << "\tFeels Like: " << forecast.m_evening.feels_like << std::endl;
        std::cout << "\tWind Speed: " << forecast.m_evening.wind_speed << std::endl;
        std::cout << "\tWind Direction: " << forecast.m_evening.wind_dir << std::endl;
        std::cout << "\tPressure (mm): " << forecast.m_evening.pressure_mm << std::endl;
        std::cout << "\tPressure (pa): " << forecast.m_evening.pressure_pa << std::endl;
        std::cout << "\tHumidity: " << forecast.m_evening.humidity << std::endl;
        std::cout << "\tPrecipitation Probability: " << forecast.m_evening.prec_prob << std::endl;
        std::cout << "\tPrecipitation Type: " << forecast.m_evening.prec_type << std::endl;
        std::cout << "\tPrecipitation Strength: " << forecast.m_evening.prec_strength << std::endl;
        std::cout << "\tDaytime: " << forecast.m_evening.daytime << std::endl;
        std::cout << "\tCondition: " << forecast.m_evening.condition << std::endl;
        std::cout << "\tCloudiness: " << forecast.m_evening.cloudness << std::endl;
        std::cout << "\tIcon: " << forecast.m_evening.icon << std::endl;

        // Ночь
        std::cout << "Night:" << std::endl;
        std::cout << "\tTemperature: " << forecast.m_night.temp << std::endl;
        std::cout << "\tFeels Like: " << forecast.m_night.feels_like << std::endl;
        std::cout << "\tWind Speed: " << forecast.m_night.wind_speed << std::endl;
        std::cout << "\tWind Direction: " << forecast.m_night.wind_dir << std::endl;
        std::cout << "\tPressure (mm): " << forecast.m_night.pressure_mm << std::endl;
        std::cout << "\tPressure (pa): " << forecast.m_night.pressure_pa << std::endl;
        std::cout << "\tHumidity: " << forecast.m_night.humidity << std::endl;
        std::cout << "\tPrecipitation Probability: " << forecast.m_night.prec_prob << std::endl;
        std::cout << "\tPrecipitation Type: " << forecast.m_night.prec_type << std::endl;
        std::cout << "\tPrecipitation Strength: " << forecast.m_night.prec_strength << std::endl;
        std::cout << "\tDaytime: " << forecast.m_night.daytime << std::endl;
        std::cout << "\tCondition: " << forecast.m_night.condition << std::endl;
        std::cout << "\tCloudiness: " << forecast.m_night.cloudness << std::endl;
        std::cout << "\tIcon: " << forecast.m_night.icon << std::endl;
    }


	return 0;
}