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
        double getOptionValue_MultiPeriod_Recursive(char);

        double getOptionValue_MultiPeriod_Memoised(char);

        double getOptionValue_MultiPeriod_DP(char);
        
    private:

        double _getOptionValue_rec(int, double, char);

        double _getOptionValue_mem(int, double, char);
    };