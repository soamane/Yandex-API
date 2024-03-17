#pragma once
#ifndef WEATHER_HPP
#define WEATHER_HPP

#include "../datatypes/datatypes.hpp"

#include <string>

// Structure of primary weather data
struct Weather
{
	int temp;
	int feels_like;
	int pressure_mm;
	int pressure_pa;
	int humidity;

	bool prec_prob;

	float wind_speed;

	std::string icon;
	std::string condition;
	std::string wind_dir;
	std::string daytime;

	Cloudiness cloudness;
	PrecType prec_type;
	PrecStrength prec_strength;
};

#endif // WEATHER_HPP
