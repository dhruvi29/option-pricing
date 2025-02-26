#include "include/binomial.h"
#include <iostream>

int main() {
    BinomialModel pricingModel = BinomialModel(200,300,4,1.2,0.8,1);
    std::cout << pricingModel.getCurrentValue();
}