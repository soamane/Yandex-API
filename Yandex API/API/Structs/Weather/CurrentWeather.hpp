#pragma once
#ifndef CURRENTWEATHER_HPP
#define CURRENTWEATHER_HPP

#include "../../Enums/YandexTypes.hpp"

#include <string>

struct CurrentWeather
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

#endif // !CURRENTWEATHER_HPP
