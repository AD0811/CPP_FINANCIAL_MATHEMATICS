#include "CartesianPoint.h"
#include "stdafx.h"
#include "testing.h"

using namespace std;

double CartesianPoint::distanceto(const CartesianPoint p){
    return sqrt(pow(x-p.x, 2) + pow(y-p.y, 2));
}

void testdistanceto(){
    CartesianPoint p1;
    p1.x = 1;
    p1.y = 1;

    CartesianPoint p2;
    p2.x = 4;
    p2.y = 5;

    double d = p1.distanceto(p2);

    ASSERT_APPROX_EQUAL(d, 5.0, 0.0001);

}