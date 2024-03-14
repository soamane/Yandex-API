#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "CurrentWeather.hpp"
#include "WeatherParts/WeatherParts.hpp"

#include <string>

struct ForecastWeather
{
	std::string m_date;

	CurrentWeather m_weather;

	MorningPart m_morning;
	DayPart m_day;
	NightPart m_night;
};

#endif // !FORECASTWEATHER_HPP
