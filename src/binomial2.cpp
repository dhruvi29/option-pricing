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
BinomialModel::~BinomialModel() {}

double BinomialModel::getCallValue() {
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

double BinomialModel::getPutValue() {
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