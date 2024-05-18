#include "UpandOutCallOption.h"

using namespace std;

double UpandOutCallOption::payoff(const vector<double>&stock_prices) const{
    double price = stock_prices.back();
    double payoff = price > strike ? price - strike : 0;
    if (payoff == 0){
        return payoff;
    }
    for (int i=0;i<stock_prices.size();i++){
        if (stock_prices[i] > barrier){
            return 0;
        }
    }
    return payoff;
}