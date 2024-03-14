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
        << "���������� �� ������ �������� �������: ";

    int conclusionValue = tempConclusion.second + humidityConclusion.second + windConclusion.second;

    struct ClothingRecommendation
    {
        std::string conditionDescription;
        std::string clothingType;
    };

    ClothingRecommendation clothingRecommendations[] = {
        {"����� �������", "����� ������ ������: ��������, ������ �������, �����, ��������, �������."},
        {"� ���� �������", "���������� ������: ������ �������, ������, �����, �����, ��������, ���������� �����."},
        {"�����", "������ ������: ��������, �������, �����, ����, ������ ������, ������ �����."},
        {"�����", "����� ������ ������: ��������, �����, ����, ������, ������ �������, ����� � ��������� �������."},
        {"����� �����", "����������� ������ ��� ������ �� ������: ������ ������ �� ������ ��� ����, �����, ��������, �����, �������������� ����, ����� � ��������� �������, �������������� ����."}
    };

    for (const auto& recommendation : clothingRecommendations) {
        if ((conclusionValue >= 0 && conclusionValue <= 3 && recommendation.conditionDescription == "����� �������") ||
            (conclusionValue >= 4 && conclusionValue <= 7 && recommendation.conditionDescription == "� ���� �������") ||
            (conclusionValue >= 8 && conclusionValue <= 11 && recommendation.conditionDescription == "�����") ||
            (conclusionValue >= 12 && conclusionValue <= 15 && recommendation.conditionDescription == "�����") ||
            (conclusionValue >= 16 && conclusionValue <= 18 && recommendation.conditionDescription == "����� �����")) {
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
    std::string conclusion = "\t> ������ �����������: ";
    int conclusionValue = 0;

    switch (tempCondition) {
        case TempCondition::VERY_COLD:
            conclusion += "����� �������";
            conclusionValue += 1;
            break;
        case TempCondition::QUITE_COLD:
            conclusion += "�������� �������";
            conclusionValue += 2;
            break;
        case TempCondition::COOL:
            conclusion += "���������";
            conclusionValue += 3;
            break;
        case TempCondition::SLIGHT_CHILL:
            conclusion += "� ���������� ��������";
            conclusionValue += 4;
            break;
        case TempCondition::WARM:
            conclusion += "�����";
            conclusionValue += 5;
            break;
        case TempCondition::HOT:
            conclusion += "�����";
            conclusionValue += 6;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetHumidityConclusion(HumidityCondition humidityCondition) {
    std::string conclusion = "\t> ������ ��������� �������: ";
    int conclusionValue = 0;

    switch (humidityCondition) {
        case HumidityCondition::DRY:
            conclusion += "����� ������";
            conclusionValue += 1;
            break;
        case HumidityCondition::COMFORT:
            conclusion += "���������� ���������";
            conclusionValue += 2;
            break;
        case HumidityCondition::HIGH:
            conclusion += "������� ������";
            conclusionValue += 3;
            break;
        case HumidityCondition::EXTREME:
            conclusion += "����� ������� ���������";
            conclusionValue += 4;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}

std::pair<std::string, int> Analyzer::GetWindConclusion(WindCondition windCondition) {
    std::string conclusion = "\t> ������ ���� �����: ";
    int conclusionValue = 0;

    switch (windCondition) {
        case WindCondition::CALM:
            conclusion += "����� ����� ���";
            conclusionValue += 1;
            break;
        case WindCondition::LIGHT_BREEZE:
            conclusion += "������ �����";
            conclusionValue += 2;
            break;
        case WindCondition::MODERATE_BREEZE:
            conclusion += "��������� �����";
            conclusionValue += 3;
            break;
        case WindCondition::STRONG_BREEZE:
            conclusion += "������� �����";
            conclusionValue += 4;
            break;
        case WindCondition::HIGH_WIND:
            conclusion += "����� ������� �����";
            conclusionValue += 5;
            break;
    }

    return std::pair(conclusion, conclusionValue);
}
