#pragma once
#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include "../api/structs/factweather.hpp"

#include "conditions/conditions.hpp"

#include <vector>
#include <sstream>
#include <utility>
#include <format>

class Analyzer
{
public:
	std::ostringstream  AnalysisWeather(const FactWeather& factWeather);

private:
	TempCondition GetTempCondition(int temp);
	HumidityCondition GetHumidityCondition(int humidity);
	WindCondition GetWindCondition(float wind_speed);

	std::pair<std::string, int> GetTempConclusion(TempCondition tempCondition);
	std::pair<std::string, int> GetHumidityConclusion(HumidityCondition humidityCondition);
	std::pair<std::string, int> GetWindConclusion(WindCondition windCondition);

private:
    struct ClothingRecommendation
    {
        std::string conditionDescription;
        std::string clothingType;
    };

    ClothingRecommendation clothingRecommendations[5] = {
        {"Very Cold", "Very warm clothing: padded jackets, warm sweaters, hats, gloves, boots."},
        {"Quite Cold", "Insulated clothing: warm sweaters, jackets, hats, scarves, gloves, insulated footwear."},
        {"Cool", "It is recommended to wear a lightweight jacket or vest, a warm sweater or cardigan paired with jeans or trousers, light footwear such as sneakers, and also to add a scarf for additional protection from the cool wind."},
        {"Warm", "Very light clothing: t-shirts, shorts, skirts, dresses, lightweight shirts, open-toed shoes."},
        {"Very Hot", "Minimal clothing for sun protection: light cotton or linen clothing, shorts, t-shirts, hats, sunglasses, open-toed shoes, sunscreen."}
    };
};

#endif // !ANALYZER_HPP
