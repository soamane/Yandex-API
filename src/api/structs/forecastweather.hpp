#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "daypart.hpp"

#include <vector>

struct ForecastWeather
{
	std::string m_date;

	DayPart m_morning;
	DayPart m_day;
	DayPart m_evening;
	DayPart m_night;

};

#endif // !FORECASTWEATHER_HPP
