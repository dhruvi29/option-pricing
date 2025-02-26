class BinomialModel{

    
    public:
        double strikePrice_, spotPrice_, interestRate_, upMove_, downMove_; 
        int timeToExpiry_;
        
        BinomialModel(double strikePrice, double spotPrice, double interestRate, double upMove, double downMove, int timeToExpiry);
        ~BinomialModel();

        double getCurrentValue();

};