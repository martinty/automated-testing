#include "utilities.h"

#include "std_lib_facilities.h"

int randomWithLimits(int lower, int upper) {
    return lower + (rand() % (upper - lower + 1));
}
