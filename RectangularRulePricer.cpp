#include "RectangularRulePricer.h"
#include "matlib.h"
#include "CallOption.h"


using namespace std;

double RectangularRulePricer :: price(BlackScholesModel &bsm, PathIndependentOption &opt){
    class Integrand : public RealFunction{
        public:
            BlackScholesModel& bsm;
            PathIndependentOption& opt;
            double evaluate(double x) const{
                double const_val = 1 / (bsm.volatility * sqrt(2 * PI * opt.get_maturity()));
                double exp_val = exp(-pow(x - log(bsm.stock_price) - bsm.drift * opt.get_maturity(), 2) / (2 * bsm.volatility * bsm.volatility * opt.get_maturity()));
                double prob = const_val * exp_val;

                double payoff = opt.payoff(exp(x));

                return isfinite(payoff) ? prob * payoff : 0;
            }

        Integrand(BlackScholesModel & _bsm, PathIndependentOption & _opt) : opt(_opt), bsm(_bsm){}
    };

    Integrand integral_obj(bsm, opt);

    double expec = integrate_over_real_line(integral_obj, 1000);
    return exp(-bsm.risk_free_rate * opt.get_maturity()) * expec;
}

static void testPriceCallOption(){
    BlackScholesModel bsm;
    bsm.stock_price = 100;
    bsm.volatility = 0.1;
    bsm.drift = 0;
    bsm.risk_free_rate = 0.1;

    CallOption copt;
    copt.strike_price = 100;
    copt.maturity = 2;
    double expec = copt.price(bsm);

    RectangularRulePricer rrp;
    double actual = rrp.price(bsm, copt);

    ASSERT_APPROX_EQUAL(expec, actual, 0.01);

}

void testRectangularRulePricer(){
    testPriceCallOption();
}