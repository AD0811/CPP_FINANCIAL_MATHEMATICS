#include "LineChart.h"

void LineChart::set_title(const string title, const string xlabel="x", const string ylabel="y"){
    _title = title;
    _xlabel = xlabel;
    _ylabel = ylabel;
}

void LineChart::top_part(){
    out <<"<html>\n";
    out <<"<head>\n";
    out <<"<script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script>\n";
    out <<"<script type =\"text/javascript\">\n";
    out <<"google.charts.load('current', {'packages':['corechart']});\n";
    out <<"google.charts.setOnLoadCallback(drawChart);\n";

    out <<"function drawChart() {\n";
    out << "var data = google.visualization.arrayToDataTable([\n";
}

void LineChart::bottom_part(){
    out <<"]);\n";
    out <<"var options = {\n";
    out<<"title: '"<<_title<<"',\n";
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

void LineChart::add_entry(double x, double y){
    _x.push_back(x);
    _y.push_back(y);
}

void LineChart::set_series(vector<double> x, vector<double> y){
    _x = x;
    _y = y;
}

void LineChart::plot(const string filename=string("chart.html")){
    out.open(filename);
    top_part();
    out <<"['"<<_xlabel<<"', '"<<_ylabel<<"'],\n";
    int n = _x.size();
    for (int i=0;i<n;i++){
        if (i!=n-1){
            out <<"["<<_x[i]<<", "<<_y[i]<<"],\n";
        }
        else{
            out <<"["<<_x[i]<<", "<<_y[i]<<"]\n";
        }
    }
    bottom_part();
    out.close();
}