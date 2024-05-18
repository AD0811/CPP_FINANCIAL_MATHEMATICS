#include<iostream>
#include "stdafx.h"
#include "geometry.h"
#include "testing.h"
using namespace std;

static const double pi = 3.14159265358979;

double area (double radius){
    return pi * pow(radius, 2);
}

double circumference (double radius){
    return pi * radius * 2;
}

int solveQuadratic(double &a, double &b, double&c){
    double root = (-b + pow(pow(b, 2) - 4 * a * c, 0.5)) / (2 * a);
    c = (-b - pow(pow(b, 2) - 4 * a * c, 0.5)) / (2 * a);
    a = root;
    b = c;
    return 0;
}

vector <double> solveQuadratic_v(double &a, double &b, double&c){
    vector<double> roots(2);
    roots.at(0) = (-b + pow(pow(b, 2) - 4 * a * c, 0.5)) / (2 * a);
    roots.at(1) = (-b - pow(pow(b, 2) - 4 * a * c, 0.5)) / (2 * a);
    return roots;
}

// Tests

static void testArea(){
    ASSERT(area(0.0001)>0);
    ASSERT(area(0.001)>area(0.002));
    ASSERT_APPROX_EQUAL(area(0.02), 1.25664, 0.001);
}

static void testCircumference(){
    ASSERT(circumference(0.0001)>0);
    ASSERT(circumference(0.001)>area(0.002));
    ASSERT_APPROX_EQUAL(circumference(0.02), 1.2566, 0.001);
}

void testGeometry(){
    TEST(testArea);
    TEST(testCircumference);

}