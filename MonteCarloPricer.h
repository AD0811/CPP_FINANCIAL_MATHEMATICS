# pragma once

#include "stdafx.h"
#include "matlib.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpandOutCallOption.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class MonteCarloPricer{
    public:
    MonteCarloPricer();
    int n_scenarios;
    double price(const PathIndependentOption &option, const BlackScholesModel &model);
    double price(const UpandOutCallOption &option, const BlackScholesModel &model, int n_steps);
    double delta(const PathIndependentOption &option, BlackScholesModel &model);
};

void test_call_and_put_option_price();

void test_up_and_out_call_option_price();