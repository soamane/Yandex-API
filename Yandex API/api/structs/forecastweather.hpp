#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "factweather.hpp"
#include "parts/dayparts.hpp"

#include <string>

struct ForecastWeather
{
	std::string m_date;

	FactWeather m_weather;

	MorningPart m_morning;
	DayPart m_day;
	NightPart m_night;
};

#endif // !FORECASTWEATHER_HPP
