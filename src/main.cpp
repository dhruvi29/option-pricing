#include "include/binomial.h"
#include "include/binomial2.h"

int main() {
    BinomialModel2 pricingModel = BinomialModel2(30,30,7,1.15,1 / 1.15, 5);
    pricingModel.getOptionValue_MultiPeriod_Recursive('C');
    pricingModel.getOptionValue_MultiPeriod_Memoised('C');
    pricingModel.getOptionValue_MultiPeriod_DP('C');

    pricingModel.getOptionValue_MultiPeriod_Recursive('P');
    pricingModel.getOptionValue_MultiPeriod_Memoised('P');
    pricingModel.getOptionValue_MultiPeriod_DP('P');

    // BinomialModel pricingModel2 = BinomialModel(30,30,7,1.15,1 / 1.15);
    // pricingModel2.getOptionValue_TheLongWay('C');
    // pricingModel2.getOptionValue_RiskNeutralProbab('C');
    // pricingModel2.getOptionValue_TheLongWay('P');
    // pricingModel2.getOptionValue_RiskNeutralProbab('P');
    // pricingModel2.getOptionValue_TheLongWay('F');

}