#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "factweather.hpp"

#include <vector>

struct ForecastWeather
{
	std::string m_date;

	Morning m_morning;
	Day m_day;
	Evening m_evening;
	Night m_night;
};

#endif // !FORECASTWEATHER_HPP
