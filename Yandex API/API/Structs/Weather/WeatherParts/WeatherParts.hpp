#pragma once
#ifndef WEATHERPARTS_HPP
#define WEATHERPARTS_HPP

#include "../../../Enums/YandexTypes.hpp"

#include <string>

struct WeatherPart
{
    int temp_min;
    int temp_avg;
    int temp_max;
    int temp_water;
    int feels_like;
    int pressure_mm;
    int pressure_pa;

    float wind_speed;

    std::string icon;
    std::string wind_dir;
    std::string condition;

    Cloudiness cloudness;
    PrecType prec_type;
    PrecStrength prec_strength;
};

struct MorningPart : WeatherPart { };
struct DayPart : WeatherPart { };
struct NightPart : WeatherPart { };

#endif // !WEATHERPARTS_HPP
