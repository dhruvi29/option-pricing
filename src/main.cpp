#include "include/binomial2.h"

int main() {
    BinomialModel2 pricingModel = BinomialModel2(30,30,7,1.15,1 / 1.15, 10);
    pricingModel.getCallValue_MultiPeriod_Recursive();
    pricingModel.getCallValue_MultiPeriod_DP();
}