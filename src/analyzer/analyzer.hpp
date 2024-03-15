#pragma once
#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "../api/structs/factweather.hpp"
#include "../api/structs/forecastweather.hpp"

#include "conditions/conditions.hpp"

#include <vector>
#include <sstream>
#include <utility>
#include <format>

class Analyzer
{
public:
	std::ostringstream  AnalysisWeather(const FactWeather& factWeather);
	std::ostringstream AnalysisWeather(const std::vector<ForecastWeather>& factWeather);

private:
	TempCondition GetTempCondition(int temp);
	HumidityCondition GetHumidityCondition(int humidity);
	WindCondition GetWindCondition(float wind_speed);

	std::pair<std::string, int> GetTempConclusion(TempCondition tempCondition);
	std::pair<std::string, int> GetHumidityConclusion(HumidityCondition humidityCondition);
	std::pair<std::string, int> GetWindConclusion(WindCondition windCondition);
};

#endif // !ANALYZER_HPP
