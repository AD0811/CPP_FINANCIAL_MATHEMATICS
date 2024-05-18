#include<algorithm>
#include "stdafx.h"
#include "matlib.h"
#include "PutOption.h"
#include "testing.h"

// using namespace std;

double PutOption::payoff(double stock_at_maturity) const{
    return stock_at_maturity<strike_price ? strike_price - stock_at_maturity : 0;
}

double PutOption::get_maturity() const{
    return maturity;
}

double PutOption::price(const BlackScholesModel &bsm) const{
    double d1 = (1/(bsm.volatility * sqrt(maturity-bsm.date))) * (log(bsm.stock_price/strike_price) + (bsm.risk_free_rate + pow(bsm.volatility, 2) / 2) * sqrt(maturity-bsm.date));
    double d2 = (1/(bsm.volatility * sqrt(maturity-bsm.date))) * (log(bsm.stock_price/strike_price) + (bsm.risk_free_rate - pow(bsm.volatility, 2) / 2) * sqrt(maturity-bsm.date));
    return -normcdf(-d1) * bsm.stock_price + normcdf(-d2)*strike_price*exp(-bsm.risk_free_rate*(maturity - bsm.date));
}

void testPutOptionPrice(){
    PutOption po;
    po.strike_price = 105;
    po.maturity = 2;

    BlackScholesModel bsm;
    bsm.date = 1;
    bsm.volatility = 0.1;
    bsm.risk_free_rate = 0.05;
    bsm.stock_price = 100;

    double price = po.price(bsm);

    ASSERT_APPROX_EQUAL(price, 3.925, 0.01);
}