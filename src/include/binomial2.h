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
        double getCallValue_v3();
        double getPutValue_v3();

        double getCallValue_v4();
        double getPutValue_v4();

        
    private:

        double _getCallValue_Rec(int, double);
        double _getPutValue_Rec(int, double);

        double _getCallValue_dp(int, double);
        double _getPutValue_dp(int, double);
    };