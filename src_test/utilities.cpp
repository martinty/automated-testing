#include "utilities.h"

#include <iostream>
#include <random>

int randomWithLimits(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void testDeviation(double compareOperand, double toOperand, double maxError,
                   string name) {
    cout << name << " = " << toOperand;
    if (abs(compareOperand - toOperand) < maxError)
        cout << ": True\n";
    else
        cout << ": False\n";
}
