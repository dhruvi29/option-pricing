class BinomialModel{

    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_;
        
        BinomialModel(double, double, double, double, double);

        double getOptionValue_TheLongWay(char);
        double getOptionValue_RiskNeutralProbab(char);
};