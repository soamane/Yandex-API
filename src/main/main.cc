#include "../api/api.hpp"

#include <iostream>

int main() {
	
	YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
	FactWeather fact = api.GetFactWeather(56.8587, 35.9176);

	return 0;
}