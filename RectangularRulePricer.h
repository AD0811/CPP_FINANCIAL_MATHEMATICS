# pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class RectangularRulePricer{
    public:
        double price(BlackScholesModel &bsm, PathIndependentOption &opt);
};

void testRectangularRulePricer();