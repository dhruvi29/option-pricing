class BinomialModel{

    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_;
        
        BinomialModel(double, double, double, double, double);
        ~BinomialModel();

        double getCallValue();
        double getPutValue();

};