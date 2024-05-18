#include<algorithm>
#include "stdafx.h"
#include "matlib.h"
#include "CallOption.h"
#include "testing.h"

// using namespace std;

double CallOption::payoff(double stock_at_maturity) const{
    return stock_at_maturity>strike_price ? stock_at_maturity - strike_price : 0;
}

double CallOption::get_maturity() const{
    return maturity;
}

double CallOption::price(const BlackScholesModel &bsm) const{
    double d1 = (1/(bsm.volatility * sqrt(maturity-bsm.date))) * (log(bsm.stock_price/strike_price) + (bsm.risk_free_rate + pow(bsm.volatility, 2) / 2) * sqrt(maturity-bsm.date));
    double d2 = (1/(bsm.volatility * sqrt(maturity-bsm.date))) * (log(bsm.stock_price/strike_price) + (bsm.risk_free_rate - pow(bsm.volatility, 2) / 2) * sqrt(maturity-bsm.date));
    return normcdf(d1) * bsm.stock_price - normcdf(d2)*strike_price*exp(-bsm.risk_free_rate*(maturity - bsm.date));
}

void testCallOptionPrice(){
    CallOption co;
    co.strike_price = 105;
    co.maturity = 2;

    BlackScholesModel bsm;
    bsm.date = 1;
    bsm.volatility = 0.1;
    bsm.risk_free_rate = 0.05;
    bsm.stock_price = 100;

    double price = co.price(bsm);
    ASSERT_APPROX_EQUAL(price, 4.046, 0.01);
}