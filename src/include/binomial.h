class BinomialModel{

    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_;
        
        BinomialModel(double, double, double, double, double);

        double getCallValue_TheLongWay();
        double getPutValue_TheLongWay();

        double getCallValue_RiskNeutralProbab();
        double getPutValue_RiskNeutralProbab();
};