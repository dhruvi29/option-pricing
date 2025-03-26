class BinomialModel{

    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_;
        
        BinomialModel(double, double, double, double, double);

        double getCallValue_v1();
        double getPutValue_v1();

        double getCallValue_v2();
        double getPutValue_v2();
};