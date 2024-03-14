#include "../api/api.hpp"
#include "../analyzer/analyzer.hpp"

#include <iostream>

int main() {
	SetConsoleOutputCP(1251);

	YandexAPI api("192ae0ad-3a7e-4b1d-891b-fa7ce08c43aa");
	std::cout << "Анализ данных г. Тверь:\n";
	FactWeather fact = api.GetFactWeather(56.8597, 35.9119);
	
	Analyzer analyzer;
	std::cout << analyzer.AnalysisWeather(fact).str();

	return 0;
}