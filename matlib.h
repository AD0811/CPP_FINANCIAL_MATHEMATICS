#pragma once
#include <vector>
#include "stdafx.h"
using namespace std;
const double PI = 3.14159265358979;

static mt19937 mersenneTwister;
 
/**
 *  Computes the cumulative
 *  distribution function of the
 *  normal distribution
 */
double normcdf( double x );
 
/**
 *  Computes the inverse of normcdf
 */
double norminv( double x );

double put_price(double curr_price, double strike_price, double time_to_maturity, double volatility, double risk_free_rate);

double call_price(double curr_price, double strike_price, double time_to_maturity, double volatility, double risk_free_rate);

double mean(const vector<double>& vec);

double prctile(vector<double>&v, double p);

double max(const vector<double>& vec);

double min(const vector<double>& vec);

vector<double> randn(int n);

vector<double> linspace(double a, double b, int n);

void rng( const string& setting );

void testMatlib();

class RealFunction{
    public:
        virtual ~RealFunction() {};
        virtual double evaluate(double x) const = 0;
};

double integrate(RealFunction &f, double a, double b, int n_steps);

class NormalPDF : public RealFunction{
    public:
        double mean;
        double variance;
        double evaluate(double x) const;
};

class Cipher{
    public:
        virtual ~Cipher() {};
        virtual string encode(string& s) const = 0;
        virtual string decode(string& s) const = 0;
};

class CeaserCipher : public Cipher{
    public:
        int _shift;
        CeaserCipher(int shift);
        string encode(string& text) const;
        string decode(string& text) const;
};

class ReverseCipher : public Cipher{
    public:
        string encode(string& text) const;
        string decode(string& text) const;
};

void testCiphers();

double integrate_over_real_line(RealFunction &f, int n_steps);

double differentiate_numerically(RealFunction &f, double x, double h);

void testNormalPDF();

void testIntegrateOverRealLine();