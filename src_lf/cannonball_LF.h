#pragma once
#include "std_lib_facilities.h"

namespace LF {

constexpr double pi = M_PI;
constexpr double gravity = 9.81;

double acclY();  // Del 1

double velY(double initVelocityY, double time);  // Del 1

double posX(double initPosition, double initVelocity, double time);  // Del 1
double posY(double initPosition, double initVelocity, double time);  // Del 1

void printTime(double time);  // Del 1

double flightTime(double initVelocityY);  // Del 1

double getUserInputTheta();        // Del 2
double getUserInputAbsVelocity();  // Del 2

double degToRad(double deg);  // Del 2

double getVelocityX(double theta, double absVelocity);               // Del 2
double getVelocityY(double theta, double absVelocity);               // Del 2
vector<double> getVelocityVector(double theta, double absVelocity);  // Del 2
double getDistanceTraveled(double velocityX, double velocityY);      // Del 2

double targetPractice(double distanceToTarget, double velocityX,
                      double velocityY);

void playTargetPractice();  // Del 3

}  // namespace LF