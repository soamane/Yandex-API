#pragma once
#ifndef CURRENTWEATHER_HPP
#define CURRENTWEATHER_HPP

#include "../enums/datatypes.hpp"

#include <string>

struct FactWeather
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

struct Morning : FactWeather { };
struct Day : FactWeather { };
struct Evening : FactWeather { };
struct Night : FactWeather { };

#endif // !CURRENTWEATHER_HPP
