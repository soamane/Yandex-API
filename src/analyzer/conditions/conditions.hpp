#pragma once
#ifndef CONDITIONS_HPP
#define CONDITIONS_HPP

enum TempCondition
{
	VERY_COLD = 0,
	QUITE_COLD = 2,
	COOL = 4,
	SLIGHT_CHILL = 6,
	WARM = 8,
	HOT = 10
};

enum HumidityCondition
{
	DRY = 0,
	COMFORT = 4,
	HIGH = 8,
	EXTREME = 10
};

enum WindCondition
{
	CALM = 0,
	LIGHT_BREEZE = 3,
	MODERATE_BREEZE = 6,
	STRONG_BREEZE = 9,
	HIGH_WIND = 10
};

#endif // !CONDITIONS_HPP
