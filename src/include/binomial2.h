class BinomialModel2{
    // With days to expiry
    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_, p_up;
        int daysToExpiry_;
        
        BinomialModel2(double, double, double, double, double, int);

        // Recursive multi-level binomial option pricing
        double getCallValue_v3();
        double getPutValue_v3();

    private:
        double _getCalValue_Rec(int, double);
};