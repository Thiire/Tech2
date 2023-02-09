/*
** EPITECH PROJECT, 2020
** CNA_trade_2019
** File description:
** main
*/

#include "bot.hpp"

Bot::Bot()
{
    std::string data;

    this->name = "";
    this->botname = "";
    this->timebank = 0;
    this->time_per_move = 0;
    this->candle_interval = 0;
    this->candle_total = 0;
    this->candle_given = 0;
    this->actual_candle = 0;
    this->initial_stack = 0;
    this->transaction_fee_percent = 0;

    std::cin >> data;
    if (data.compare("settings")) {
        std::cerr << "no settings" << std::endl;
        exit (84);
    }
    while (!data.compare("settings")) {
        std::cin >> data;
        if (!data.compare("player_names")) {
            std::cin >> data;
            this->name = data;
        } else if (!data.compare("your_bot")) {
            std::cin >> data;
            this->botname = data;
        } else if (!data.compare("timebank")) {
            std::cin >> data;
            this->timebank = std::stoi(data);
        } else if (!data.compare("time_per_move")) {
            std::cin >> data;
            this->time_per_move = std::stoi(data);
        } else if (!data.compare("candle_interval")) {
            std::cin >> data;
            this->candle_interval = std::stoi(data);
        } else if (!data.compare("candle_format")) {
            std::cin >> data;
            std::vector<std::string> format = this->StrToWordVector(data, ',', 0);
            for (size_t idx = 0; idx < format.size(); idx++) {
                if (!format[idx].compare("pair")) {
                    this->candle_format.push_back(PAIR);
                } else if (!format[idx].compare("date")) {
                    this->candle_format.push_back(DATE);
                } else if (!format[idx].compare("high")) {
                    this->candle_format.push_back(HIGH);
                } else if (!format[idx].compare("low")) {
                    this->candle_format.push_back(LOW);
                } else if (!format[idx].compare("open")) {
                    this->candle_format.push_back(OPEN);
                } else if (!format[idx].compare("close")) {
                    this->candle_format.push_back(CLOSE);
                } else if (!format[idx].compare("volume")) {
                    this->candle_format.push_back(VOLUME);
                }
            }
        } else if (!data.compare("candles_total")) {
            std::cin >> data;
            this->candle_total = std::stoi(data);
        } else if (!data.compare("candles_given")) {
            std::cin >> data;
            this->candle_given = std::stoi(data);
        } else if (!data.compare("initial_stack")) {
            std::cin >> data;
            this->initial_stack = std::stoi(data);
        } else if (!data.compare("transaction_fee_percent")) {
            std::cin >> data;
            this->transaction_fee_percent = std::stof(data);
        } else {
            std::cerr << "Wrong settings" << std::endl;
            exit (0);
        }
        std::cin >> data;
    }
}

Bot::~Bot()
{
}

float Bot::mobile_average(int index)
{
    float result = 0;
    int size = this->candle_given / 5;

    if (this->stock[index].second.size() < size) {
        return -1;
    }
    for (int idx = this->stock[index].second.size(); idx > this->stock[index].second.size() - size; idx--) {
        result += this->stock[index].second[idx - 1];
    }
    return result / size;
}

float Bot::standard_deviation(int index)
{
    float result = 0;
    float average = 0;
    int size = this->candle_given / 5;

    if (this->stock[index].second.size() < size) {
        return -1;
    }
    average = this->mobile_average(index);
    for (int idx = this->stock[index].second.size(); idx > this->stock[index].second.size() - size; idx--) { 
        result += (std::pow((std::fabs(this->stock[index].second[idx - 1] - average)), 2));
    }
    return std::sqrt(result / size);
}

float Bot::upper_band(int index)
{
    int size = this->candle_given / 5;
    float result = 0;

    if (this->stock[index].second.size() < size) {
        return -1;
    }
    result = this->mobile_average(index) + this->standard_deviation(index) * 2;
    return result;
}

float Bot::lower_band(int index)
{
    int size = this->candle_given / 5;
    float result = 0;

    if (this->stock[index].second.size() < size) {
        return -1;
    }
    result = this->mobile_average(index) - this->standard_deviation(index) * 2;
    return result;
}

void Bot::start()
{
    std::vector<std::string> tmp;
    int stonksTop = 0;
    int stonksBottom = 0;
    std::string data;
    int passed = 0;

    while (1) {
        passed = 0;
        std::cin >> data;
        if (!data.compare("update")) {
            std::cin >> data;
            if (!data.compare("game")) {
                std::cin >> data;
                if (!data.compare("next_candles")) {
                    std::cin >> data;
                    this->stockStock(data);
                } else if (!data.compare("stacks")) {
                    std::cin >> data;
                    this->stockMoney(data);
                }
            }
        } else if (!data.compare("action")) {
            std::cin >> data;
            if (!data.compare("order")) {
                std::cin >> data;
                if (std::stoi(data) == this->timebank) {
                    for (size_t idx = 0; idx < this->stock.size(); idx++) {
                        stonksTop = (this->stock[idx].second.back() / this->upper_band(idx)) * 100 - 100;
                        stonksBottom = (this->lower_band(idx) / this->stock[idx].second.back()) * 100 - 100;
                        if (stonksTop >= 8) {
                            tmp = this->StrToSaveVector(this->stock[idx].first, '_', 0);
                            for (size_t idy = 0; idy < this->money.size(); idy++) {
                                if (!this->money[idy].first.compare(tmp[1])) {
                                    if (this->money[idy].second > 0) {
                                        std::cout << "sell " << this->stock[idx].first << " " << this->money[idy].second / this->stock[idx].second.back() / 2 << std::endl;
                                        std::cerr << "sell [" << this->stock[idx].first << "] : " << this->money[idy].second / this->stock[idx].second.back() / 2 << ", stonks : " << stonksTop << std::endl;
                                        passed++;
                                        break;
                                    }
                                }
                            }
                        } else if (stonksBottom >= 8) {
                            tmp = this->StrToSaveVector(this->stock[idx].first, '_', 0);
                            for (size_t idy = 0; idy < this->money.size(); idy++) {
                                if (!this->money[idy].first.compare(tmp[0])) {
                                    if (this->money[idy].second > 0) {
                                        std::cout << "buy " << this->stock[idx].first << " " << this->money[idy].second / this->stock[idx].second.back() / 2 << std::endl;
                                        std::cerr << "buy [" << this->stock[idx].first << "] : " << this->money[idy].second / this->stock[idx].second.back() / 2 << ", stonks : " << stonksBottom << std::endl;
                                        passed++;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (passed == 0) {
                        std::cout << "pass" << std::endl;
                    }
                }
            }
        }
    }
}

std::vector<std::string> Bot::StrToWordVector(std::string &data, char c, char stop)
{
    std::vector<std::string> stock;

    for (size_t idx = 0; idx < data.size(); idx++) {
        if (data[idx] == c) {
            stock.push_back(data.substr(0, idx));
            data = data.substr(idx + 1, data.size() - idx);
            idx = 0;
        } else if (data[idx] == stop) {
            stock.push_back(data.substr(0, idx));
            data = data.substr(idx + 1, data.size() - idx);
            return stock;
        }
    }
    if (data.size() > 0) {
        stock.push_back(data.substr(0, data.size()));
        data = "";
    }
    return stock;
}

std::vector<std::string> Bot::StrToSaveVector(std::string data, char c, char stop)
{
    std::vector<std::string> stock;

    for (size_t idx = 0; idx < data.size(); idx++) {
        if (data[idx] == c) {
            stock.push_back(data.substr(0, idx));
            data = data.substr(idx + 1, data.size() - idx);
            idx = 0;
        } else if (data[idx] == stop) {
            stock.push_back(data.substr(0, idx));
            data = data.substr(idx + 1, data.size() - idx);
            return stock;
        }
    }
    if (data.size() > 0) {
        stock.push_back(data.substr(0, data.size()));
        data = "";
    }
    return stock;
}

int Bot::getFormatIndex(Format format)
{
    for (size_t idx = 0; idx < this->candle_format.size(); idx++) {
        if (format == this->candle_format[idx]) {
            return idx;
        }
    }
    return 0;
}

void Bot::stockStock(std::string data)
{
    std::vector<std::string> tmp;
    int idx = 0;
    bool empty = this->stock.empty();

    while (!data.empty()) {
        tmp = this->StrToWordVector(data, ',', ';');
        if (empty) {
            this->stock.push_back(std::pair<std::string, std::vector<float> >(tmp[this->getFormatIndex(PAIR)], std::vector<float>()));
        }
        this->stock[idx].second.push_back((std::stof(tmp[this->getFormatIndex(HIGH)]) + std::stof(tmp[this->getFormatIndex(LOW)])) / 2.0);
        idx++;
    }
}

void Bot::stockMoney(std::string data)
{
    std::vector<std::string> tmp;
    int idx = 0;
    bool empty = this->money.empty();

    while (!data.empty()) {
        tmp = this->StrToWordVector(data, ':', ',');
        if (empty) {
            this->money.push_back(std::pair<std::string, float>(tmp[0], std::stof(tmp[1])));
        }
        this->money[idx].second = std::stof(tmp[1]);
        idx++;
    }
}