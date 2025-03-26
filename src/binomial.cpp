#include "include/binomial.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

BinomialModel::BinomialModel(double spotPrice, double strikePrice, double interestRate, double upMove, double downMove) {
    // validations and percentage conversions
    if (strikePrice < 0) {
        throw std::invalid_argument("Strike price cannot be negative");
    }
    if (spotPrice < 0) {
        throw std::invalid_argument("Spot price cannot be negative");
    }
    if (interestRate < 0) {
        throw std::invalid_argument("Interest Rate cannot be negative");
    }
    if (upMove < 1) {
        throw std::invalid_argument("Up move factor should be greater than or equal to 1");
    }
    if (downMove < 0) {
        throw std::invalid_argument("Down move factor cannot be negative");
    }
    if (downMove > 1) {
        throw std::invalid_argument("Down move factor cannot be greater than 1");
    }
    
    strikePrice_ = strikePrice;
    spotPrice_ = spotPrice;
    interestRate_ = interestRate / 100;
    upMove_ = upMove;
    downMove_ = downMove;

    std::cout << "Strike Price: " << strikePrice_ << "\n";
    std::cout << "Spot Price: " << spotPrice_  << "\n";
    std::cout << "Interest Rate: " << interestRate_  << "\n";
    std::cout << "Up move factor: " << upMove_  << "\n";
    std::cout << "Down move factor: " << downMove_  << "\n";
}

double BinomialModel::getCallValue_v1() {

    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double c1u = std::max(0.0, s1u - strikePrice_);
    double c1d = std::max(0.0, s1d - strikePrice_);
    double hedgeRatio = (c1u - c1d) / (s1u - s1d);
    // v1u = v1d -> A portfolio of shares and options 
    // i.e. Sell some shares & some call options to buy the sold shares in future
    // or You could also - Buy some shares and write call options
    // v1u = h * s1u - c1u; v1d = h * s1d - c1d;
    double v1 = hedgeRatio * s1u - c1u;
    double v0 = v1 / (1 + interestRate_);
    // v0 = h * s0 - c0; c0 = h * s0 - v0
    double c0 = hedgeRatio * spotPrice_ - v0;


    std::cout << "S1: " << s1u << " " << s1d << "\n";
    std::cout << "C1: " << c1u << " " << c1d << "\n";

    std::cout << "Hedge Ratio: " << hedgeRatio << "\n";
    std::cout << "Value of portfolio at time = 1: " << v1 << "\n";
    std::cout << "Value of portfolio at time = 0: " << v0 << "\n";
    std::cout << "**************************\n";
    std::cout << "Value of Call: " << c0 <<"\n";
    std::cout << "**************************\n";
    return c0;
}

double BinomialModel::getPutValue_v1() {

    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double p1u = std::max(0.0, strikePrice_ - s1u);
    double p1d = std::max(0.0, strikePrice_ - s1d);
    double hedgeRatio = (p1u - p1d) / (s1u - s1d);
    // v1u = v1d -> A portfolio of shares and options 
    // i.e. Buy some shares & buy some put options to sell the bought shares in future
    // v1u = h * s1u - c1u; v1d = h * s1d - c1d;
    double v1 = hedgeRatio * s1u - p1u;
    double v0 = v1 / (1 + interestRate_);
    // v0 = h * s0 - c0; c0 = h * s0 - v0
    double p0 = hedgeRatio * spotPrice_ - v0;


    std::cout << "S1: " << s1u << " " << s1d << "\n";
    std::cout << "P1: " << p1u << " " << p1d << "\n";

    std::cout << "Hedge Ratio: " << hedgeRatio << "\n";
    std::cout << "Value at time = 1: " << v1 << "\n";
    std::cout << "Value at time = 0: " << v0 << "\n";
    std::cout << "**************************\n";
    std::cout << "Value of Put: " << p0 <<"\n";
    std::cout << "**************************\n";
    return p0;
}

double BinomialModel::getCallValue_v2() {
    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double c1u = std::max(0.0, s1u - strikePrice_);
    double c1d = std::max(0.0, s1d - strikePrice_);

    // p = (1 + RF - D)/(U-D) -> Risk free probability of upmove
    // probablity of down move = 1 - probability of upmove
    double p_up = (1 + interestRate_ - downMove_) / (upMove_ - downMove_);

    // c1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double c1 = p_up * c1u + (1 - p_up) * c1d;
    double c0 = c1 / (1 + interestRate_);

    std::cout << "S1: " << s1u << " " << s1d << "\n";
    std::cout << "C1: " << c1u << " " << c1d << "\n";

    std::cout << "Value of cal at time = 1: " << c1 << "\n";
    std::cout << "**************************\n";
    std::cout << "Value of call at time = 0: " << c0 << "\n";
    std::cout << "**************************\n";
    return c0;
}

double BinomialModel::getPutValue_v2() {
    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double p1u = std::max(0.0, strikePrice_ - s1u);
    double p1d = std::max(0.0, strikePrice_ - s1d);

    // p = (1 + RF - D)/(U-D) -> Risk free probability of upmove
    // probablity of down move = 1 - probability of upmove
    double p_up = (1 + interestRate_ - downMove_) / (upMove_ - downMove_);

    // p1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double p1 = p_up * p1u + (1 - p_up) * p1d;
    double p0 = p1 / (1 + interestRate_);

    std::cout << "S1: " << s1u << " " << s1d << "\n";
    std::cout << "P1: " << p1u << " " << p1d << "\n";

    std::cout << "Value of put at time = 1: " << p1 << "\n";
    std::cout << "**************************\n";
    std::cout << "Value of put at time = 0: " << p0 << "\n";
    std::cout << "**************************\n";
    return p0;
}