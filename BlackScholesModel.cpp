#include "BlackScholesModel.h"
#include "stdafx.h"
#include "matlib.h"
#include "LineChart.h"

using namespace std;

vector<double> BlackScholesModel::generate_price_path(double to_date, int n_steps, double drift) const{
    vector<double> path (2*n_steps, 0.0);
    vector<double> e = randn(n_steps);

    double dt = (to_date - date) / n_steps;
    double a = (drift - volatility * volatility * 0.5) * dt;
    double b = volatility*sqrt(dt);
    double current_log_price = log(stock_price);
    for (int i=0;i<n_steps;i++){
        double log_price = current_log_price + a + b*e[i];
        path[i] = exp(log_price);
        current_log_price = log_price;
    }
    for (int i=n_steps;i<2*n_steps;i++){
        double log_price = current_log_price + a - b*e[i];
        path[i] = exp(log_price);
        current_log_price = log_price;
    }
    return path;
}

vector<double> BlackScholesModel::generate_price_path(double to_date, int n_steps) const{
    return generate_price_path(to_date, n_steps, drift);
}

vector<double> BlackScholesModel::generate_risk_neutral_price_path(double to_date, int n_steps) const{
    return generate_price_path(to_date, n_steps, risk_free_rate);
}

void test_price_path(){
    BlackScholesModel bsm;
    bsm.risk_free_rate = 0.05;
    bsm.volatility = 0.1;
    bsm.stock_price = 100;
    bsm.date = 2.0;

    int n_steps = 1000;
    double maturity = 4.0;

    vector<double> path = bsm.generate_price_path(maturity, n_steps);
    double dt = (maturity - bsm.date) / n_steps;
    vector<double> times = linspace(dt, maturity, n_steps);
    LineChart linechart;
    linechart.set_series(times, path);
    linechart.set_title("Stock price path", "time", "price");
    string filename = "example_price_path.html";
    linechart.plot(filename);
}

void test_risk_neutral_price_path(){
    rng("default");
    BlackScholesModel bsm;
    bsm.risk_free_rate = 0.05;
    bsm.volatility = 0.1;
    bsm.stock_price = 100;
    bsm.date = 2;
    int n_paths = 10000;
    int n_steps = 5;
    double maturity = 4;

    vector<double> final_prices(n_paths, 0);
    for (int i=0;i<n_paths;i++){
        final_prices[i] = bsm.generate_risk_neutral_price_path(maturity, n_steps).back();
    }
    ASSERT_APPROX_EQUAL(mean(final_prices), exp(bsm.risk_free_rate*(maturity - bsm.date))*bsm.stock_price, 0.5);
}