#include "../api/api.hpp"

#include <iostream>

int main() {
	YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
	FactWeather fact = api.GetFactWeather(12.4354325, 34.234234);
	std::cout << fact.temp;
   
	return 0;
}