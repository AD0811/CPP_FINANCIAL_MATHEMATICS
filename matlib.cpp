#include "matlib.h"
#include "stdafx.h"
#include "testing.h"
#include<algorithm>
using namespace std;
 
static const double ROOT_2_PI = sqrt( 2.0 * PI );
 
 
static inline double hornerFunction(
        double x,
        double a0,
        double a1) {
    return a0 + x*a1;
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2) {
    return a0 + x*hornerFunction( x, a1, a2);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3) {
    return a0 + x*hornerFunction( x, a1, a2, a3);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                       double a5) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                       double a5, double a6) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                       double a5, double a6, double a7) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7);
}
 
static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
                       double a5, double a6, double a7, double a8) {
    return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7, a8);
}
 

double normcdf( double x ) {
    if (x<0) {
        return 1-normcdf(-x);
    }
    double k = 1/(1 + 0.2316419*x);
    double poly = hornerFunction(k,
                                 0.0, 0.319381530, -0.356563782,
                                 1.781477937,-1.821255978,1.330274429);
    double approx = 1.0 - 1.0/ROOT_2_PI * exp(-0.5*x*x) * poly;
    return approx;
}
 
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;
 
double norminv( double x ) {
    // We use Moro's algorithm
    double y = x - 0.5;
    if (y<0.42 && y>-0.42) {
        double r = y*y;
        return y*hornerFunction(r,a0,a1,a2,a3)/hornerFunction(r,1.0,b1,b2,b3,b4);
    } else {
        double r;
        if (y<0.0) {
            r = x;
        } else {
            r = 1.0 - x;
        }
        double s = log( -log( r ));
        double t = hornerFunction(s,c0,c1,c2,c3,c4,c5,c6,c7,c8);
        if (x>0.5) {
            return t;
        } else {
            return -t;
        }
    }
}


double put_price(double curr_price, double strike_price, double time_to_maturity, double volatility, double risk_free_rate){
    double d1 = (1 / (volatility * time_to_maturity)) * (log(curr_price/strike_price) + ((risk_free_rate + pow(volatility, 2) / 2) * pow(time_to_maturity, 0.5)));
    double d2 = (1 / (volatility * time_to_maturity)) * (log(curr_price/strike_price) + ((risk_free_rate - pow(volatility, 2) / 2) * pow(time_to_maturity, 0.5)));
    return normcdf(-d2) * strike_price * exp(-risk_free_rate * time_to_maturity) - normcdf(-d1) * curr_price;
}


double call_price(double curr_price, double strike_price, double time_to_maturity, double volatility, double risk_free_rate){
    double d1 = (1 / (volatility * time_to_maturity)) * (log(curr_price/strike_price) + ((risk_free_rate + pow(volatility, 2) / 2) * pow(time_to_maturity, 0.5)));
    double d2 = (1 / (volatility * time_to_maturity)) * (log(curr_price/strike_price) + ((risk_free_rate - pow(volatility, 2) / 2) * pow(time_to_maturity, 0.5)));
    return -normcdf(d2) * strike_price * exp(-risk_free_rate * time_to_maturity) + normcdf(d1) * curr_price;
}


double mean(const vector<double>& vec){
    double sum = 0;
    for (int i=0;i<vec.size();i++){
        sum += vec[i];
    }
    return sum / vec.size();
}

double standard_deviation(const vector<double>& vec, bool population=true){
    double err_sum = 0;
    double mean_value = mean(vec);
    for (int i=0;i<vec.size();i++){
        err_sum += pow(vec[i]-mean_value, 2);
    }
    if (population){
        return pow(err_sum/vec.size(), 0.5);
    }
    else{
        return pow(err_sum/(vec.size()-1), 0.5);
    }
}

double max(const vector<double>& vec){
    double res = vec[0];
    for (int i=0; i<vec.size();i++){
        if (vec[i] > res){
            res = vec[i];
        }
    }
    return res;
}

double min(const vector<double>& vec){
    double res = vec[0];
    for (int i=0; i<vec.size();i++){
        if (vec[i] < res){
            res = vec[i];
        }
    }
    return res;
}

vector<double> randuniform(int n){
    vector<double> res(n);
    for (int i=0;i<n;i++){
        res[i] = (mersenneTwister() + 0.5) /  (mersenneTwister.max() + 1);
    }
    return res;
}

vector<double> randn(int n){
    vector<double> res(n);
    default_random_engine gen;
    normal_distribution<double> distribution(0, 1);
    for (int i=0;i<n;i++){
        res[i] = distribution(gen);
    }
    return res;
}

vector<double> randn_bm(int n){
    vector<double> u1 = randuniform(n);
    vector<double> u2 = randuniform(n);
    for(int i=0;i<n;i++){
        u1[i] = pow(-2*log(u1[i]), 0.5) * cos(2*PI*u2[i]);
    }
    return u1;
}

double prctile(vector<double>&v, double p){
    vector<double>copy = v;
    int n = copy.size();
    sort(copy.begin(), copy.end());
    if (p==0){
        return copy[0];
    }
    if (p==100){
        return copy[n-1];
    }
    double ind_needed = p*n/100 + 0.5 - 1;
    int ind_lower = floor(ind_needed);
    int ind_upper = ceil(ind_needed);
    if (ind_lower == ind_upper){
        return copy[ind_lower];
    }
    else{
        return copy[ind_lower] + (copy[ind_upper]-copy[ind_lower]) * (ind_needed - ind_lower);
    }
}

vector <double> linspace(double a, double b, int n){
    vector<double> res;
    if (n <= 0){
        return res;
    }
    res.push_back(a);
    if (n == 1){
        return res;
    }
    double increment = (b-a) / (n-1);
    for (int i=1;i<n-1;i++){
        res.push_back(res[i-1] + increment);
    }
    res.push_back(b);
    return res;
}

void rng( const string& setting ){
    ASSERT(setting=="default");
    mersenneTwister.seed(mt19937::default_seed);
}


double integrate(RealFunction &f, double a, double b, int n_steps=10000){
    double h = (b-a) / n_steps;
    double sum = 0;
    a += 0.5 * h;
    for (int i=0;i<n_steps;i++){
        sum += f.evaluate(a);
        a += h;
    }
    return sum*h;
}

double NormalPDF::evaluate(double x) const{
    return (1 / (sqrt(variance) * ROOT_2_PI)) * exp(-pow(x-mean, 2) / (2*variance));
}

double integrate_to_infinity(RealFunction &f, double start_point, int n_steps){
    class AlteredFunction : public RealFunction{
        public:
            double x;
            RealFunction& f;
            double evaluate(double s) const{
                return 1 / (s*s)*f.evaluate(1 / s + x - 1);
            }
            AlteredFunction(double x, RealFunction& f) : x(x), f(f)
            {}
    };
    AlteredFunction alt(start_point, f);
    return integrate(alt, 0, 1, n_steps);
}

double integrate_from_infinity(RealFunction &f, double end_point, int n_steps){
    class AlteredFunction : public RealFunction{
        public:
            RealFunction& f;
            double evaluate(double x) const{
                return f.evaluate(-x);
            }
            AlteredFunction(RealFunction& f) : f(f)
            {}
    };
    AlteredFunction alt(f);
    return integrate_to_infinity(alt, -end_point, n_steps);
}

double integrate_over_real_line(RealFunction &f, int n_steps){
    return integrate_to_infinity(f, 0, n_steps) + integrate_from_infinity(f, 0, n_steps);
}

double differentiate_numerically(RealFunction &f, double x, double h=1e-6){
    return (f.evaluate(x+h) - f.evaluate(x)) / h;
}

CeaserCipher :: CeaserCipher(int shift=3){
    _shift = shift;
}

string CeaserCipher :: encode(string &text) const{
    string encoded[text.length()];
    for(int i=0;i<text.length();i++){
        int temp = text[i];
        if(temp<=90 and temp>=65){
            if (temp + _shift>90){
                encoded[i] = char(65 + (temp + _shift - 90) - 1);
            }
            else{
                encoded[i] = char(temp + _shift);
            }
        }
        else if(temp<=122 and temp>=97){
            if (temp + _shift>122){
                encoded[i] = char(97 + (temp + _shift - 122) - 1);
            }
            else{
                encoded[i] = char(temp + _shift);
            }
        }
        else{
            encoded[i] = text[i];
        }
    }
}

string CeaserCipher :: decode(string &text) const{
    string decoded[text.length()];
    for(int i=0;i<text.length();i++){
        int temp = text[i];
        if(temp<=90 and temp>=65){
            if (temp - _shift<65){
                decoded[i] = char(90 - (65 - temp + _shift) + 1);
            }
            else{
                decoded[i] = char(temp - _shift);
            }
        }
        else if(temp<=122 and temp>=97){
            if (temp + _shift>122){
                decoded[i] = char(122 - (97 - temp + _shift) + 1);
            }
            else{
                decoded[i] = char(temp - _shift);
            }
        }
        else{
            decoded[i] = text[i];
        }
    }
}

string ReverseCipher :: encode(string &text) const{
    string encoded[text.length()];
    for(int i=0;i<text.length();i++){
        int temp = text[i];
        if(temp<=90 and temp>=65){
            encoded[i] = char(90 - (temp - 65));
        }
        else if(temp<=122 and temp>=97){
            encoded[i] = char(122 - (temp - 97));
        }
        else{
            encoded[i] = text[i];
        }
    }
}

string ReverseCipher :: decode(string &text) const{
    return encode(text);
}

// Tests

static void testNormCdf() {
  // test bounds
  ASSERT(normcdf(0.3)>0);
  ASSERT(normcdf(0.3)<1);
  // test extreme values
  ASSERT_APPROX_EQUAL(normcdf(-1e10), 0, 0.001);
  ASSERT_APPROX_EQUAL(normcdf(1e10), 1.0, 0.001);
  // test increasing
  ASSERT(normcdf(0.3)<normcdf(0.5));
  // test symmetry
  ASSERT_APPROX_EQUAL(normcdf(0.3),
    1 - normcdf(-0.3), 0.0001);
  ASSERT_APPROX_EQUAL(normcdf(0.0), 0.5, 0.0001);
  // test inverse
  ASSERT_APPROX_EQUAL(normcdf(norminv(0.3)),
    0.3, 0.0001);
  // test well known value
  ASSERT_APPROX_EQUAL(normcdf(1.96), 0.975, 0.001);
}
 
static void testNormInv() {
    ASSERT_APPROX_EQUAL(norminv(0.975), 1.96, 0.01 );
}

static void testPutPrice(){
    ASSERT(put_price(5, 10, 2, 0.5, 0.06)>0);
    ASSERT_APPROX_EQUAL(put_price(7, 10, 2, 0.5, 0.06), 2.205, 0.01);
}

static void testMean(){
    vector <double> v {1, 2, 3, 4, 5};
    ASSERT_APPROX_EQUAL(mean(v), 3, 0.1);
}

static void teststandardDeviation(){
    vector <double> v {1, 2, 3, 4, 5};
    ASSERT_APPROX_EQUAL(standard_deviation(v), 1.41, 0.1);
    ASSERT_APPROX_EQUAL(standard_deviation(v, false), 1.58, 0.1);
}

static void testMaxMin(){
    vector <double> v {1, 2, 3, 4, 5};
    ASSERT(max(v)==5);
    ASSERT(min(v)==1);
}

static void testRandUniform(){
    vector<double> res = randuniform(3);
    for(int i=0;i<3;i++){
        ASSERT(res[i]<1 && res[i]>=0);
    }
}


static void testRandN(){
    vector<double> res = randn(1000);
    ASSERT_APPROX_EQUAL(mean(res), 0, 0.001);
    ASSERT_APPROX_EQUAL(standard_deviation(res), 1, 0.001);
    res = randn_bm(3);
    ASSERT_APPROX_EQUAL(mean(res), 0, 0.001);
    ASSERT_APPROX_EQUAL(standard_deviation(res), 1, 0.001);
}

void testNormalPDF(){
    NormalPDF nrm;
    nrm.mean = 0;
    nrm.variance = 1;
    ASSERT_APPROX_EQUAL(integrate(nrm, -1.96, 1.96), 0.95, 0.001);
}

void testIntegrateOverRealLine(){
    NormalPDF nrm;
    nrm.mean = 0;
    nrm.variance = 1;
    ASSERT_APPROX_EQUAL(integrate_from_infinity(nrm, 0.5, 10000), normcdf(0.5), 0.0001);
}

void testCipher(Cipher& to_test){
    string s = "asdf ;lkj g h";
    ASSERT(s == to_test.decode(to_test.encode(s)));
}

void testCiphers(){
    CeaserCipher cc;
    testCipher(cc);
    ReverseCipher rc;
    testCipher(rc);
}
 
void testMatlib() {
    TEST( testNormInv );
    TEST( testNormCdf );
    TEST(testPutPrice);
    TEST(testMean);
    TEST(teststandardDeviation);
    TEST(testMaxMin);
    TEST(testRandUniform);
    TEST(testRandN);
}