#pragma once

class CartesianPoint{
    public:
    double x;
    double y;
    double distanceto(const CartesianPoint p);
};

void testdistanceto();