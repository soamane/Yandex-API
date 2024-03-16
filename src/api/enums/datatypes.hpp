#pragma once
#ifndef YANDEXTYPES_HPP
#define YANDEXTYPES_HPP

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

#endif // !YANDEXTYPES_HPP
