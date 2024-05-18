#pragma once

#include "stdafx.h"
#include "matlib.h"

class UpandOutCallOption{
    public:
        double maturity;
        double strike;
        double barrier;
        double payoff(const vector<double>&stock_prices) const;
};