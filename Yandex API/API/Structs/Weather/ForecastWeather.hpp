#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "CurrentWeather.hpp"
#include "WeatherParts/WeatherParts.hpp"

#include <string>

// �������� ������� � �������� �� part-���������

struct ForecastWeather
{
	std::string date;

	CurrentWeather weather;

	MorningPart morning;
	DayPart day;
	NightPart night;
};

#endif // !FORECASTWEATHER_HPP
