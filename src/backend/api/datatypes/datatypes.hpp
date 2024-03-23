#pragma once
#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

/* 
	This file contains predefined enumerations 
	of specific weather data as specified in the Yandex API.
*/


enum Cloudiness
{
	CLEAR,
	PARTLY,
	SIGNIFICANT,
	CLOUDY,
	OVERCAST
};

enum PrecType
{
	NO_TYPE,
	RAIN,
	SLEET,
	SNOW,
	HAIL
};

enum PrecStrength
{
	ZERO,
	WEAK,
	AVERAGE,
	STRONG,
	VERY_STRONG
};

#endif // !DATA_TYPES_HPP
