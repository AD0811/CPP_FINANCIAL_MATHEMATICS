#pragma once
using namespace std;

#include<vector>

class BlackScholesModel{
    public:
        double stock_price;
        double volatility;
        double risk_free_rate;
        double date;
        double drift;
        vector<double> generate_price_path(double to_date, int n_steps) const;
        vector<double> generate_risk_neutral_price_path(double to_date, int n_steps) const;
    private:
        vector<double> generate_price_path(double to_date, int n_steps, double drift) const;
};

void test_price_path();
void test_risk_neutral_price_path();