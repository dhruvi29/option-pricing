#include <vector>
#include <map>

class BinomialModel2{
    // With days to expiry
    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_, p_up;
        int daysToExpiry_;

        std::vector<std::map<double, double>> dp;
        
        BinomialModel2(double, double, double, double, double, int);

        // Recursive multi-level binomial option pricing
        double getCallValue_MultiPeriod_Recursive();
        double getPutValue_MultiPeriod_Recursive();

        double getCallValue_MultiPeriod_Memoised();
        double getPutValue_MultiPeriod_Memoised();

        double getCallValue_MultiPeriod_DP();
        double getPutValue_MultiPeriod_DP();
        
    private:

        double _getCallValue_rec(int, double);
        double _getPutValue_rec(int, double);

        double _getCallValue_mem(int, double);
        double _getPutValue_mem(int, double);
    };