#pragma once
#ifndef FORECASTWEATHER_HPP
#define FORECASTWEATHER_HPP

#include "weather.hpp"

#include <vector>

struct ForecastWeather
{
	std::string m_date;

	Weather m_morning;
	Weather m_day;
	Weather m_evening;
	Weather m_night;

};

#endif // !FORECASTWEATHER_HPP
