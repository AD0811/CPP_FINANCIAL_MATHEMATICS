#include <iostream>
#include "matlib.h"
#include "geometry.h"
#include "charts.h"
#include"stdafx.h"
#include "CallOption.h"
#include "PutOption.h"
#include "CartesianPoint.h"
#include "BlackScholesModel.h"
#include "MonteCarloPricer.h"
#include "RectangularRulePricer.h"

using namespace std;
 
int main() {
    testRectangularRulePricer();
    return 0;
}
