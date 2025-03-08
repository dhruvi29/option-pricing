#include "include/binomial.h"

int main() {
    BinomialModel pricingModel = BinomialModel(50,55,3,1.2,0.84);
    pricingModel.getCallValue();
    pricingModel.getPutValue();
}