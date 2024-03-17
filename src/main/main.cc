#include "../api/api.hpp"

#include <iostream>

int main() {
	try {
		YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
		Weather weather = api.GetWeather(90, 180);

	} catch (const std::exception& exception) {
		std::cerr << exception.what();
	}
	return 0;
}