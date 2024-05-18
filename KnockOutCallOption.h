# pragma once

#include "ContinousTimeOption.h"
#include "stdafx.h"

class KnockOutCallOption : public ContinousTimeOption{
    public:
        double barrier;
        double get_maturity() const;
        double payoff(vector<double>&stock_prices, vector<double>&times) const;
};