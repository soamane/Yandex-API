#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "CurrentWeather.hpp"
#include "WeatherParts/WeatherParts.hpp"

#include <string>

class ForecastWeather
{
	int yd_temp;

	std::string date;
	std::string sunrise;
	std::string sunset;

	CurrentWeather weather;

	MorningPart morning;
	DayPart day;
	NightPart night;
};

#endif // !FORECASTWEATHER_HPP
