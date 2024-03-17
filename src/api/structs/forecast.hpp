#pragma once
#ifndef FORECAST_HPP
#define FORECAST_HPP

#include "weather.hpp"

#include <vector>

struct Forecast
{
	std::string date;
	Weather morning;
	Weather day;
	Weather evening;
	Weather night;
};

#endif // !FORECAST_HPP
