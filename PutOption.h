#pragma once
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class PutOption : public PathIndependentOption{
    public:
    double strike_price;
    double maturity;
    double payoff(double stock_at_maturity) const;
    double price(const BlackScholesModel &bsm) const;
    double get_maturity() const;
};

void testPutOptionPrice();