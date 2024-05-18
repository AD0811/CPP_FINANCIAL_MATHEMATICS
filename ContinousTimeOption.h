#pragma once

#include "stdafx.h"

class ContinousTimeOption{
    public:
        virtual ~ContinousTimeOption() {};
        virtual double get_maturity() const = 0;
        virtual double payoff(vector<double>&stock_prices, vector<double>&times) const = 0;
};