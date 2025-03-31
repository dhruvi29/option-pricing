#include "include/binomial2.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>

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

double BinomialModel2::_getOptionValue_rec(int daysToExpiry, double spotPrice, char optionType) {

    if (daysToExpiry == 0) return std::max(0.0, optionType == 'C' ? spotPrice - strikePrice_ : strikePrice_ - spotPrice);

    double s1u = spotPrice * upMove_;
    double s1d = spotPrice * downMove_;
    double o1u = _getOptionValue_rec(daysToExpiry - 1, s1u, optionType);
    double o1d = _getOptionValue_rec(daysToExpiry - 1, s1d, optionType);

    // o1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double o1 = p_up * o1u + (1 - p_up) * o1d;
    double o0 = o1 / (1 + interestRate_ / 365);

    return o0;

}

double BinomialModel2::getOptionValue_MultiPeriod_Recursive(char optionType) {
    double o0 = _getOptionValue_rec(daysToExpiry_, spotPrice_, optionType);
    std::cout << (optionType == 'C' ? "Call" : "Put") <<" Option value at time = 0: " << o0 << "\n";
    return o0;
}

double BinomialModel2::_getOptionValue_mem(int daysToExpiry, double spotPrice, char optionType) {

    if (daysToExpiry == 0) return std::max(0.0, optionType == 'C' ? spotPrice - strikePrice_ : strikePrice_ - spotPrice);

    if (dp[daysToExpiry].count(spotPrice) > 0) return dp[daysToExpiry][spotPrice];

    double s1u = spotPrice * upMove_;
    double s1d = spotPrice * downMove_;
    double o1u = _getOptionValue_mem(daysToExpiry - 1, s1u, optionType);
    double o1d = _getOptionValue_mem(daysToExpiry - 1, s1d, optionType);

    // o1 (Expected future payoff) = probability-weighted value of upmove and downmove
    double o1 = p_up * o1u + (1 - p_up) * o1d;
    double o0 = o1 / (1 + interestRate_ / 365);

    return dp[daysToExpiry][spotPrice] = o0;

}

double BinomialModel2::getOptionValue_MultiPeriod_Memoised(char optionType) {

    dp.clear();
    dp.resize(daysToExpiry_ + 1, {});
    double o0 = _getOptionValue_mem(daysToExpiry_, spotPrice_, optionType);
    std::cout << (optionType == 'C' ? "Call" : "Put") <<" Option value at time = 0: " << o0 << "\n";
    return o0;
}


double BinomialModel2::getOptionValue_MultiPeriod_DP(char optionType) {
    
    int noOfSpotIndices = daysToExpiry_ * 2 + 1;
    std::vector<std::vector<double>> dp(daysToExpiry_ + 1, std::vector<double>(noOfSpotIndices, 0));

    double pv_factor = (1 + interestRate_ / 365); // present value divisor

    for (int day = 0 ; day <= daysToExpiry_ ; day++) {

        for (int spotIndex = day ; spotIndex < noOfSpotIndices - day ; spotIndex++) {

            if (day == 0) {
                double spotPrice = spotPrice_ * std::pow(upMove_, spotIndex - daysToExpiry_);
                dp[day][spotIndex] = std::max(0.0, optionType == 'C' ? spotPrice - strikePrice_ : strikePrice_ - spotPrice);
            }
            else dp[day][spotIndex] = (p_up * dp[day - 1][spotIndex + 1] + (1 - p_up) * dp[day - 1][spotIndex - 1]) / pv_factor;
        }
    }

    std::cout << (optionType == 'C' ? "Call" : "Put") <<" Option value at time = 0: " << dp[daysToExpiry_][daysToExpiry_] << "\n";
    return dp[daysToExpiry_][daysToExpiry_];

}