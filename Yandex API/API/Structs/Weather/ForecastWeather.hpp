#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "CurrentWeather.hpp"
#include "WeatherParts/WeatherParts.hpp"

#include <string>

// дописать парсинг и внимание на part-структуры

struct ForecastWeather
{
	std::string date;

	CurrentWeather weather;

	MorningPart morning;
	DayPart day;
	NightPart night;
};

#endif // !FORECASTWEATHER_HPP
