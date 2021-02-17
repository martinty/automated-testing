#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#define BOOST_TEST_MODULE oving03
#include <stdlib.h>

#include <boost/test/unit_test.hpp>
#include <ctime>
#include <vector>

using namespace std;

#include "src_lf/cannonball_LF.h"
#include "src_lf/utilities_LF.h"
#include "src_test/cannonball.h"
#include "src_test/utilities.h"

namespace test {
constexpr double err = 0.001;
double diff(double a, double b) { return std::abs(a - b); }
bool operator==(const vector<double>& lhs, const vector<double>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (int i{0}; i < lhs.size(); i++) {
        if (test::diff(lhs.at(i), rhs.at(i)) > err) return false;
    }
    return true;
}
}  // namespace test

BOOST_AUTO_TEST_CASE(cannonball_h) {
    BOOST_CHECK_CLOSE(acclY(), LF::acclY(), test::err);
    BOOST_CHECK_CLOSE(velY(10, 2), LF::velY(10, 2), test::err);
    BOOST_CHECK_CLOSE(posX(0, 10, 2), LF::posX(0, 10, 2), test::err);
    BOOST_CHECK_CLOSE(posY(0, 10, 2), LF::posY(0, 10, 2), test::err);
    BOOST_CHECK_CLOSE(flightTime(10), LF::flightTime(10), test::err);
    BOOST_CHECK_CLOSE(degToRad(60), LF::degToRad(60), test::err);
    BOOST_CHECK_CLOSE(getVelocityX(45, 45), LF::getVelocityX(45, 45),
                      test::err);
    BOOST_CHECK_CLOSE(getVelocityY(45, 45), LF::getVelocityY(45, 45),
                      test::err);
    vector<double> velVec = getVelocityVector(45, 45);
    vector<double> velVecLF = LF::getVelocityVector(45, 45);
    BOOST_TEST(test::operator==(velVec, velVecLF));
    BOOST_CHECK_CLOSE(velVec[0], velVecLF[0], test::err);
    BOOST_CHECK_CLOSE(velVec[1], velVecLF[1], test::err);

    // BOOST_CHECK_CLOSE(targetPractice(400, 45, 45),
    //                   LF::targetPractice(400, 45, 45), test::err);
}

BOOST_AUTO_TEST_CASE(utilities_h) {
    srand(10);
    int randValue = randomWithLimits(10, 20);
    srand(10);
    int randValueLF = LF::randomWithLimits(10, 20);
    BOOST_TEST(randValue == randValueLF);
}
