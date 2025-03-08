#include "include/binomial.h"

int main() {
    BinomialModel pricingModel = BinomialModel(30,30,7,1.15,0.87);
    pricingModel.getCallValue();
    pricingModel.getPutValue();
}