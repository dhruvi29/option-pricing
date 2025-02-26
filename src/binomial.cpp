#include "include/binomial.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

BinomialModel::BinomialModel(double strikePrice, double spotPrice, double interestRate, double upMove, double downMove, int timeToExpiry) {
    // validations and percentage conversions
    if (timeToExpiry < 0) {
        throw std::invalid_argument("Time to expiry cannot be negative");
    }
    
    this->strikePrice_ = strikePrice;
    this->spotPrice_ = spotPrice;
    this->interestRate_ = interestRate / 100;
    this->upMove_ = upMove;
    this->downMove_ = downMove;
    this->timeToExpiry_ = timeToExpiry;

    
}
BinomialModel::~BinomialModel() {}

double BinomialModel::getCurrentValue() {
    double s1u = spotPrice_ * upMove_;
    double s1d = spotPrice_ * downMove_;

    std::cout << s1u << " " << s1d << "\n";

    double c1u = std::max(0.0, s1u - strikePrice_);
    double c1d = std::max(0.0, s1d - strikePrice_);

    std::cout << c1u << " " << c1d << "\n";

    double probabOfUpmove = (1 + interestRate_ - downMove_) / (upMove_ - downMove_);
    double probabOfDownmove = 1 - probabOfUpmove;

    std::cout << probabOfUpmove << " " << probabOfDownmove << "\n";

    double c1 = c1u * probabOfUpmove + c1d * probabOfDownmove;

    double c0 = c1 / (1 + interestRate_);

    std::cout << c1 << " " << c0 << "\n";

    return c0;
}

