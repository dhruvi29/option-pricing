#include "include/binomial2.h"

int main() {
    BinomialModel2 pricingModel = BinomialModel2(30,30,7,1.15,0.87, 1);
    // pricingModel.getCallValue_v3();
    pricingModel.getPutValue_v3();
}