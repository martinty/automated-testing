#pragma once
#include <string>
using namespace std;

int randomWithLimits(int min, int max);

void testDeviation(double compareOperand, double toOperand, double maxError,
                   string name);