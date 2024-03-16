#include "analyzer.hpp"

std::ostringstream Analyzer::AnalysisWeather(const FactWeather& factWeather) {
    TempCondition tempCondition = GetTempCondition(factWeather.temp);
    HumidityCondition humidityCondition = GetHumidityCondition(factWeather.humidity);
    WindCondition windCondition = GetWindCondition(factWeather.wind_speed);

    auto tempConclusion = GetTempConclusion(tempCondition);
    auto humidityConclusion = GetHumidityConclusion(humidityCondition);
    auto windConclusion = GetWindConclusion(windCondition);

    std::ostringstream oss;
    oss << std::format("{} ({}/10)\n", tempConclusion.first, tempConclusion.second)
        << std::format("{} ({}/10)\n", humidityConclusion.first, humidityConclusion.second)
        << std::format("{} ({}/10)\n", windConclusion.first, windConclusion.second);

    int conclusionValue = tempConclusion.second + humidityConclusion.second + windConclusion.second;

    struct ClothingRecommendation
    {
        std::string conditionDescription;
        std::string clothingType;
    };

    ClothingRecommendation clothingRecommendations[] = {
        {"Very Cold", "Very warm clothing: padded jackets, warm sweaters, hats, gloves, boots."},
        {"Quite Cold", "Insulated clothing: warm sweaters, jackets, hats, scarves, gloves, insulated footwear."},
        {"Cool", "It is recommended to wear a lightweight jacket or vest, a warm sweater or cardigan paired with jeans or trousers, light footwear such as sneakers, and also to add a scarf for additional protection from the cool wind."},
        {"Warm", "Very light clothing: t-shirts, shorts, skirts, dresses, lightweight shirts, open-toed shoes."},
        {"Very Hot", "Minimal clothing for sun protection: light cotton or linen clothing, shorts, t-shirts, hats, sunglasses, open-toed shoes, sunscreen."}
    };

    for (const auto& recommendation : clothingRecommendations) {
        if ((conclusionValue >= 0 && conclusionValue <= 3 && recommendation.conditionDescription == "Very Cold") ||
            (conclusionValue >= 4 && conclusionValue <= 7 && recommendation.conditionDescription == "Quite Cold") ||
            (conclusionValue >= 8 && conclusionValue <= 11 && recommendation.conditionDescription == "Cool") ||
            (conclusionValue >= 12 && conclusionValue <= 15 && recommendation.conditionDescription == "Warm") ||
            (conclusionValue >= 16 && conclusionValue <= 18 && recommendation.conditionDescription == "Very Hot")) {
            oss << std::format("Weather Conditions Conclusion: {}\n{}", recommendation.conditionDescription, recommendation.clothingType);
        }
    }

    return oss;
}

TempCondition Analyzer::GetTempCondition(int temp) {
    if (temp <= -25) {
        return TempCondition::VERY_COLD;
    } else if (temp <= -15) {
        return TempCondition::QUITE_COLD;
    } else if (temp <= 0) {
        return TempCondition::COOL;
    } else if (temp <= 10) {
        return TempCondition::SLIGHT_CHILL;
    } else if (temp <= 25) {
        return TempCondition::WARM;
    } else {
        return TempCondition::HOT;
    }
}

HumidityCondition Analyzer::GetHumidityCondition(int humidity) {
    if (humidity < 30) {
        return HumidityCondition::DRY;
    } else if (humidity <= 60) {
        return HumidityCondition::COMFORT;
    } else if (humidity <= 80) {
        return HumidityCondition::HIGH;
    } else {
        return HumidityCondition::EXTREME;
    }
}

WindCondition Analyzer::GetWindCondition(float wind_speed) {
    if (wind_speed < 1.0) {
        return WindCondition::CALM;
    } else if (wind_speed < 5.0) {
        return WindCondition::LIGHT_BREEZE;
    } else if (wind_speed < 12.0) {
        return WindCondition::MODERATE_BREEZE;
    } else if (wind_speed < 20.0) {
        return WindCondition::STRONG_BREEZE;
    } else {
        return WindCondition::HIGH_WIND;
    }
}

std::pair<std::string, int> Analyzer::GetTempConclusion(TempCondition tempCondition) {
    std::string conclusion = "\t> Temperature Analysis: ";
    int conclusionValue = 0;

    switch (tempCondition) {
        case TempCondition::VERY_COLD:
            conclusion += "very cold";
            conclusionValue += 1;
            break;
        case TempCondition::QUITE_COLD:
            conclusion += "quite cold";
            conclusionValue += 2;
            break;
        case TempCondition::COOL:
            conclusion += "cool";
            conclusionValue += 3;
            break;
        case TempCondition::SLIGHT_CHILL:
            conclusion += "slightly chilly";
            conclusionValue += 4;
            break;
        case TempCondition::WARM:
            conclusion += "warm";
            conclusionValue += 5;
            break;
        case TempCondition::HOT:
            conclusion += "hot";
            conclusionValue += 6;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetHumidityConclusion(HumidityCondition humidityCondition) {
    std::string conclusion = "\t> Humidity Analysis: ";
    int conclusionValue = 0;

    switch (humidityCondition) {
        case HumidityCondition::DRY:
            conclusion += "dry weather";
            conclusionValue += 1;
            break;
        case HumidityCondition::COMFORT:
            conclusion += "comfortable humidity";
            conclusionValue += 2;
            break;
        case HumidityCondition::HIGH:
            conclusion += "humid weather";
            conclusionValue += 3;
            break;
        case HumidityCondition::EXTREME:
            conclusion += "very high humidity";
            conclusionValue += 4;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetWindConclusion(WindCondition windCondition) {
    std::string conclusion = "\t> Wind Strength Analysis: ";
    int conclusionValue = 0;

    switch (windCondition) {
        case WindCondition::CALM:
            conclusion += "almost no wind";
            conclusionValue += 1;
            break;
        case WindCondition::LIGHT_BREEZE:
            conclusion += "light breeze";
            conclusionValue += 2;
            break;
        case WindCondition::MODERATE_BREEZE:
            conclusion += "moderate breeze";
            conclusionValue += 3;
            break;
        case WindCondition::STRONG_BREEZE:
            conclusion += "strong breeze";
            conclusionValue += 4;
            break;
        case WindCondition::HIGH_WIND:
            conclusion += "very strong wind";
            conclusionValue += 5;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}
