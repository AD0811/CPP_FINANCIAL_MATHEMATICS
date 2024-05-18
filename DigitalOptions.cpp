#include "stdafx.h"
#include "DigitalOptions.h"

using namespace std;

double DigitalCallOption::payoff(double stock_at_maturity) const{
    return stock_at_maturity>strike_price ? 1 : 0;
}

double DigitalCallOption::get_maturity() const{
    return maturity;
}

double DigitalPutOption::payoff(double stock_at_maturity) const{
    return stock_at_maturity<strike_price ? 1 : 0;
}

double DigitalPutOption::get_maturity() const{
    return maturity;
}