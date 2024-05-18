#include "charts.h"
#include "matlib.h"
#include <vector>
#include <string>

using namespace std;

static void top_part(ostream & out){
    out <<"<html>\n";
    out <<"<head>\n";
    out <<"<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out <<"<script type =\"text/javascript\">\n";
    out <<"google.charts.load('current', {'packages':['corechart']});\n";
    out <<"google.charts.setOnLoadCallback(drawChart);\n";

    out <<"function drawChart() {\n";
    out << "var data = google.visualization.arrayToDataTable([\n";
}

static void bottom_part(ostream &out, const string& title){
    out <<"]);\n";
    out <<"var options = {\n";
    out<<"title: '"<<title<<"',\n";
    out<<"curveType: 'function',\n";
    out<<"legend: { position: 'bottom' }\n";
    out<<"};\n";
    out<<"var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));\n";
    out<<"chart.draw(data, options);\n";    
    out<<"}\n";
    out<<"</script>\n";
    out<<"</head>\n";
    out<<"<body>\n";
    out<<"<div id=\"curve_chart\" style=\"width: 900px; height: 500px\"></div>\n";
    out<<"</body>\n";
    out<<"</html>\n";
}

static void writelinechart(ostream &out, const vector<double>&x, const vector<double>&y, const string& xlabel, const string& ylabel){
    out <<"['"<<xlabel<<"', '"<<ylabel<<"'],\n";
    int n = x.size();
    for (int i=0;i<n;i++){
        if (i!=n-1){
            out <<"["<<x[i]<<", "<<y[i]<<"],\n";
        }
        else{
            out <<"["<<x[i]<<", "<<y[i]<<"]\n";
        }
    }

}

void call_premium(){
    int n = 1000;
    vector<double> curr_price(n);
    vector<double> call_premium_vec(n);
    for(double i=0;i<n;i++){
        curr_price[i] = 50 + (i*100/n);
        call_premium_vec[i] = call_price(curr_price[i], 100, 1, 0.2, 0.05);
    }
    ofstream out;
    out.open("call_premium.html");
    top_part(out);
    writelinechart(out, curr_price, call_premium_vec, "Current Price", "Call Premium");
    bottom_part(out, "Call Option Premium vs Current Stock Price");
}

void hist(const vector<double>&v, int n){
    vector<double>copy = v;
    sort(copy.begin(), copy.end());
    double bin_size = (max(copy) - min(copy)) / n;
    vector<double>y(n, 0);
    vector<double>x(n);
    double val = min(copy) + bin_size;
    int res_itr = 0;
    cout<<max(copy)<<" "<<min(copy)<<" "<<bin_size<<"\n";
    for(int i=0;i<copy.size();i++){
        if (i>=copy.size()-2){
            cout<<copy[i]<<" "<<copy[i-1]<<"\n";
        }
        if (copy[i]<=val){
            y[res_itr]++;
            x[res_itr] = copy[i];
        }
        else{
            res_itr++;
            y[res_itr]++;
            x[res_itr] = copy[i];
            val += bin_size;
        }
    }
    int zero_ind;
    for(int i=n-1;i>=0;i--){
        if(x[i] != 0){
            zero_ind = i;
            break;
        }
    }
    x = vector<double>(x.begin(), x.begin()+zero_ind);
    y = vector<double>(y.begin(), y.begin()+zero_ind);
    ofstream out;
    out.open("hist.html");
    top_part(out);
    writelinechart(out, x, y, "x", "Frequency");
    bottom_part(out, "Frequency - Histogram");
}


static void testwritelinechart(){
    ofstream out;
    out.open("chart.html");
    vector<double> x(41);
    vector<double> y(41);
    for(int i=0;i<41;i++){
        x[i] = i-20;
        y[i] = x[i] * x[i];
    }
    top_part(out);
    writelinechart(out, x, y, "x", "y");
    bottom_part(out, "Curve y = x^2");
    out.close();
}

void testCharts(){
    testwritelinechart();
}