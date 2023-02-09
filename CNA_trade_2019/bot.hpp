/*
** EPITECH PROJECT, 2020
** CNA_trade_2019
** File description:
** Bot
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cmath>

enum Format {
    PAIR,
    DATE,
    HIGH,
    LOW,
    OPEN,
    CLOSE,
    VOLUME,
};

class Bot {
    public:
        Bot();
        ~Bot();
        float mobile_average(int index);
        float upper_band(int index);
        float lower_band(int index);
        float standard_deviation(int index);
        void start();


    protected:
    private:
        std::string name;
        std::string botname;
        int timebank;
        int time_per_move;
        int candle_interval;
        int candle_total;
        int candle_given;
        int actual_candle;
        int initial_stack;
        int transaction_fee_percent;
        std::vector<Format> candle_format;
        std::vector<std::pair<std::string,std::vector<float> > > stock;
        std::vector<std::pair<std::string, float> > money;

        std::vector<std::string> StrToWordVector(std::string &data, char c, char stop);
        std::vector<std::string> StrToSaveVector(std::string data, char c, char stop);
        void stockStock(std::string data);
        void stockMoney(std::string data);
        int getFormatIndex(Format format);
};

#endif /* !BOT_HPP_ */
