#include "../api/api.hpp"

#include <iostream>

int main() {
	YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");

	std::vector<ForecastWeather> forecast = api.GetForecastWeather(12.345, 55.342, 5);


	return 0;
}