#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file
#define BOOST_TEST_MODULE oving03
#include <boost/test/unit_test.hpp>
#include <ctime>

#include "src_lf/cannonball_LF.h"
#include "src_lf/utilities_LF.h"
#include "src_test/cannonball.h"
#include "src_test/utilities.h"

BOOST_AUTO_TEST_CASE(cannonball_h) {
    BOOST_TEST(acclY() == LF::acclY());
    BOOST_TEST(velY(10, 2) == LF::velY(10, 2));
    BOOST_TEST(posX(0, 10, 2) == LF::posX(0, 10, 2));
    BOOST_TEST(posY(0, 10, 2) == LF::posY(0, 10, 2));
    BOOST_TEST(flightTime(10) == LF::flightTime(10));
    BOOST_TEST(degToRad(60) == LF::degToRad(60));
    BOOST_TEST(getVelocityX(45, 45) == LF::getVelocityX(45, 45));

    vector<double> velVec = getVelocityVector(45, 45);
    vector<double> velVecLF = LF::getVelocityVector(45, 45);

    BOOST_TEST(velVec[0] == velVecLF[0]);
    BOOST_TEST(velVec[1] == velVecLF[1]);

    /*
    BOOST_TEST(targetPractice(400, 45, 45) == LF::targetPractice(400, 45, 45));
    */
}

BOOST_AUTO_TEST_CASE(utilities_h) {
    srand(10);
    int randValue = randomWithLimits(10, 20);
    srand(10);
    int randValueLF = LF::randomWithLimits(10, 20);
    BOOST_TEST(randValue == randValueLF);
}
