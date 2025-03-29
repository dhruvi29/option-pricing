#include "include/binomial2.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

BinomialModel2::BinomialModel2(double spotPrice, double strikePrice, double interestRate, double upMove, double downMove, int daysToExpiry) {
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
    if (daysToExpiry < 0) {
        throw std::invalid_argument("Down move factor cannot be greater than 1");
    }
    
    strikePrice_ = strikePrice;
    spotPrice_ = spotPrice;
    interestRate_ = interestRate / 100;
    upMove_ = upMove;
    downMove_ = downMove;
    daysToExpiry_ = daysToExpiry;

    // p = (1 + RF - D)/(U-D) -> Risk free probability of upmove
    // probablity of down move = 1 - probability of upmove
    p_up = (1 + interestRate_ / 365 - downMove_) / (upMove_ - downMove_);
    
    std::cout << "Strike Price: " << strikePrice_ << "\n";
    std::cout << "Spot Price: " << spotPrice_  << "\n";
    std::cout << "Interest Rate: " << interestRate_  << "\n";
    std::cout << "Up move factor: " << upMove_  << "\n";
    std::cout << "Down move factor: " << downMove_  << "\n";
    std::cout << "Probablility of upmove: " << p_up << "\n";
}

double BinomialModel2::_getCallValue_Rec(int daysToExpiry, double spotPrice) {

    if (daysToExpiry == 0) return std::max(0.0, spotPrice - strikePrice_);

    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double c1u = _getCallValue_Rec(daysToExpiry - 1, s1u);
    double c1d = _getCallValue_Rec(daysToExpiry - 1, s1d);

    // c1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double c1 = p_up * c1u + (1 - p_up) * c1d;
    double c0 = c1 / (1 + interestRate_ / 365);

    return c0;

}

double BinomialModel2::_getPutValue_Rec(int daysToExpiry, double spotPrice) {

    if (daysToExpiry == 0) return std::max(0.0, strikePrice_ - spotPrice);

    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;
    double p1u = _getCallValue_Rec(daysToExpiry - 1, s1u);
    double p1d = _getCallValue_Rec(daysToExpiry - 1, s1d);

    // c1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double p1 = p_up * p1u + (1 - p_up) * p1d;
    double p0 = p1 / (1 + interestRate_ / 365);

    return p0;

}

double BinomialModel2::getCallValue_v3() {
    
    double c0 = _getCallValue_Rec(daysToExpiry_, spotPrice_);
    std::cout << "C0: " << c0 << "\n";
    return c0;
}

double BinomialModel2::getPutValue_v3() {
    double p0 = _getPutValue_Rec(daysToExpiry_, spotPrice_);
    std::cout << "P0: " << p0 << "\n";
    return p0;
}