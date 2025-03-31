#include "include/binomial2.h"

int main() {
    BinomialModel2 pricingModel = BinomialModel2(30,30,7,1.15,1 / 1.15, 5);
    pricingModel.getCallValue_MultiPeriod_Recursive();
    pricingModel.getCallValue_MultiPeriod_Memoised();
    pricingModel.getCallValue_MultiPeriod_DP();

    pricingModel.getPutValue_MultiPeriod_Recursive();
    pricingModel.getPutValue_MultiPeriod_Memoised();
    pricingModel.getPutValue_MultiPeriod_DP();
}