# pragma once

class PathIndependentOption{
    public:
        virtual ~PathIndependentOption() {};
        virtual double get_maturity() const = 0;
        virtual double payoff(double stock_at_maturity) const = 0;
};