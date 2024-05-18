#include "MonteCarloPricer.h"

using namespace std;

MonteCarloPricer::MonteCarloPricer(){
    n_scenarios = 10000;
}

double MonteCarloPricer::price(const PathIndependentOption &option, const BlackScholesModel &model){
    double total = 0;
    for (int i=0;i<n_scenarios;i++){
        double est_price  = model.generate_risk_neutral_price_path(option.get_maturity(), 1).back();
        total += option.payoff(est_price);
    }
    double mean = total/n_scenarios;
    double time_left = option.get_maturity() - model.date;
    return exp(-model.risk_free_rate*time_left) * mean;
}

double MonteCarloPricer::price(const UpandOutCallOption &option, const BlackScholesModel &model, int n_steps){
    double total = 0;
    for (int i=0;i<n_scenarios;i++){
        vector<double> price_path  = model.generate_risk_neutral_price_path(option.maturity, n_steps);
        total += option.payoff(price_path);
    }
    double mean = total/n_scenarios;
    double time_left = option.maturity - model.date;
    return exp(-model.risk_free_rate*time_left) * mean;
}

double MonteCarloPricer::delta(const PathIndependentOption &option, BlackScholesModel &model){
    double h = model.stock_price*10e-6;
    model.stock_price += h;
    rng("default");
    double p1 = price(option, model);
    model.stock_price -= 2*h;
    rng("default");
    double p2 = price(option, model);
    model.stock_price += h;
    return (p1 - p2) / (2*h);
}

void test_call_and_put_option_price(){
    rng("default");
    MonteCarloPricer mcp;

    PutOption opt;
    opt.maturity = 2;
    opt.strike_price = 100;

    BlackScholesModel bsm;
    bsm.date = 1;
    bsm.risk_free_rate = 0.05;
    bsm.stock_price = 80;
    bsm.drift = 0.1;
    
    double price = mcp.price(opt, bsm);
    double expected = opt.price(bsm);
    ASSERT_APPROX_EQUAL(price, expected, 0.1);

    CallOption copt;
    copt.maturity = 2;
    copt.strike_price = 100;
    price = mcp.price(copt, bsm);
    expected = copt.price(bsm);
    ASSERT_APPROX_EQUAL(price, expected, 0.1);
}

void test_up_and_out_call_option_price(){
    rng("default");
    MonteCarloPricer mcp;
    UpandOutCallOption opt;
    opt.maturity = 2;
    opt.strike = 100;
    opt.barrier = 200;

    BlackScholesModel bsm;
    bsm.date = 1;
    bsm.risk_free_rate = 0.05;
    bsm.stock_price = 80;
    bsm.drift = 0.1;
    
    ASSERT(mcp.price(opt, bsm, 100)>0);

    opt.barrier = 100;
    ASSERT_APPROX_EQUAL(mcp.price(opt, bsm, 100), 0, 0.5);
}
