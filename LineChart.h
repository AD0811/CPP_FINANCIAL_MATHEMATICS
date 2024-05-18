#pragma once
#include "stdafx.h"

using namespace std;

class LineChart{
    public:
    void add_entry(double x, double y);
    void set_series(vector<double>x, vector<double>y);
    void set_title(string title, string xlabel, string ylabel);
    void plot(const string filename);
    private:
    ofstream out;
    string _xlabel;
    string _ylabel;
    string _title;
    vector<double>_x;
    vector<double>_y;
    void top_part();
    void bottom_part();
};