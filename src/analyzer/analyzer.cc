#include "analyzer.hpp"

std::ostringstream Analyzer::AnalysisWeather(const FactWeather& factWeather) {
    TempCondition tempCondition = GetTempCondition(factWeather.temp);
    HumidityCondition humidityCondition = GetHumidityCondition(factWeather.humidity);
    WindCondition windCondition = GetWindCondition(factWeather.wind_speed);

    std::pair<std::string, int> tempConclusion = GetTempConclusion(tempCondition);
    std::pair<std::string, int> humidityConclusion = GetHumidityConclusion(humidityCondition);
    std::pair<std::string, int> windConclusion = GetWindConclusion(windCondition);

    std::ostringstream oss;
    oss << tempConclusion.first << ' ' << '(' << tempConclusion.second << '/' << "10" << ')' << '\n'
        << humidityConclusion.first << ' ' << '(' << humidityConclusion.second << '/' << "10" << ')' << '\n'
        << windConclusion.first << ' ' << '(' << windConclusion.second << '/' << "10" << ')' << '\n'
        << "Заключение по данным погодных условий: ";

    int conclusionValue = tempConclusion.second + humidityConclusion.second + windConclusion.second;

    struct ClothingRecommendation
    {
        std::string conditionDescription;
        std::string clothingType;
    };

    ClothingRecommendation clothingRecommendations[] = {
        {"Очень холодно", "Очень теплая одежда: пуховики, теплые свитера, шапки, перчатки, ботинки."},
        {"В меру холодно", "Утепленная одежда: теплые свитера, куртки, шапки, шарфы, перчатки, утепленная обувь."},
        {"Тепло", "Легкая одежда: футболки, рубашки, шорты, юбки, легкие куртки, легкая обувь."},
        {"Жарко", "Очень легкая одежда: футболки, шорты, юбки, платья, легкие рубашки, обувь с открытыми носками."},
        {"Очень жарко", "Минимальная одежда для защиты от солнца: легкая одежда из хлопка или льна, шорты, футболки, шляпы, солнцезащитные очки, обувь с открытыми носками, солнцезащитный крем."}
    };

    for (const auto& recommendation : clothingRecommendations) {
        if ((conclusionValue >= 0 && conclusionValue <= 3 && recommendation.conditionDescription == "Очень холодно") ||
            (conclusionValue >= 4 && conclusionValue <= 7 && recommendation.conditionDescription == "В меру холодно") ||
            (conclusionValue >= 8 && conclusionValue <= 11 && recommendation.conditionDescription == "Тепло") ||
            (conclusionValue >= 12 && conclusionValue <= 15 && recommendation.conditionDescription == "Жарко") ||
            (conclusionValue >= 16 && conclusionValue <= 18 && recommendation.conditionDescription == "Очень жарко")) {
            oss << recommendation.conditionDescription << '\n' << recommendation.clothingType;
        }
    }

    return oss;
}

std::ostringstream Analyzer::AnalysisWeather(const std::vector<ForecastWeather>& factWeather) {
    return std::ostringstream();
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
    std::string conclusion = "\t> Анализ температуры: ";
    int conclusionValue = 0;

    switch (tempCondition) {
        case TempCondition::VERY_COLD:
            conclusion += "очень холодно";
            conclusionValue += 1;
            break;
        case TempCondition::QUITE_COLD:
            conclusion += "довольно холодно";
            conclusionValue += 2;
            break;
        case TempCondition::COOL:
            conclusion += "прохладно";
            conclusionValue += 3;
            break;
        case TempCondition::SLIGHT_CHILL:
            conclusion += "с прохладным воздухом";
            conclusionValue += 4;
            break;
        case TempCondition::WARM:
            conclusion += "тепло";
            conclusionValue += 5;
            break;
        case TempCondition::HOT:
            conclusion += "жарко";
            conclusionValue += 6;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetHumidityConclusion(HumidityCondition humidityCondition) {
    std::string conclusion = "\t> Анализ влажности воздуха: ";
    int conclusionValue = 0;

    switch (humidityCondition) {
        case HumidityCondition::DRY:
            conclusion += "сухая погода";
            conclusionValue += 1;
            break;
        case HumidityCondition::COMFORT:
            conclusion += "комфортная влажность";
            conclusionValue += 2;
            break;
        case HumidityCondition::HIGH:
            conclusion += "влажная погода";
            conclusionValue += 3;
            break;
        case HumidityCondition::EXTREME:
            conclusion += "очень высокая влажность";
            conclusionValue += 4;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetWindConclusion(WindCondition windCondition) {
    std::string conclusion = "\t> Анализ силы ветра: ";
    int conclusionValue = 0;

    switch (windCondition) {
        case WindCondition::CALM:
            conclusion += "ветра почти нет";
            conclusionValue += 1;
            break;
        case WindCondition::LIGHT_BREEZE:
            conclusion += "легкий ветер";
            conclusionValue += 2;
            break;
        case WindCondition::MODERATE_BREEZE:
            conclusion += "умеренный ветер";
            conclusionValue += 3;
            break;
        case WindCondition::STRONG_BREEZE:
            conclusion += "сильный ветер";
            conclusionValue += 4;
            break;
        case WindCondition::HIGH_WIND:
            conclusion += "очень сильный ветер";
            conclusionValue += 5;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}
