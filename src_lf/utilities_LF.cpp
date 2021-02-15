#include "utilities_LF.h"

#include "std_lib_facilities.h"

namespace LF {

int randomWithLimits(int lower, int upper) {
    return lower + (rand() % (upper - lower + 1));
}

}  // namespace LF
