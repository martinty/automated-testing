#define _USE_MATH_DEFINES
#include "cannonball.h"

#include <cmath>
#include <iostream>

#include "TextColor.h"
#include "cannonball_viz.h"
#include "utilities.h"

double acclY() { return -9.81; }

double velY(double initVelocityY, double time) {
    return initVelocityY + acclY() * time;
}

double posX(double initPosition, double initVelocity, double time) {
    return initPosition + initVelocity * time;
}

double posY(double initPosition, double initVelocity, double time) {
    return initPosition + initVelocity * time + acclY() * time * time / 2;
}

void printTime(double time) {
    int sec = (int)time;
    int min = sec / 60;
    int h = min / 60;
    double restTime = time - sec;
    sec = sec % 60;
    min = min % 60;
    cout << h << " hour(s), " << min << " minute(s), " << sec + restTime
         << " second(s) \n";
}

double flightTime(double initVelocityY) { return -2 * initVelocityY / acclY(); }

double getUserInputTheta() {
    double theta;
    cout << "Theta: ";
    cin >> theta;
    return theta;
}

double getUserInputAbsVelocity() {
    double absVel;
    cout << "Absolute velocity: ";
    cin >> absVel;
    return absVel;
}

double degToRad(double deg) { return deg / 180 * M_PI; }

double getVelocityX(double theta, double absVelocity) {
    return absVelocity * cos(degToRad(theta));
}

double getVelocityY(double theta, double absVelocity) {
    return absVelocity * sin(degToRad(theta));
}

vector<double> getVelocityVector(double theta, double absVelocity) {
    return vector<double>{getVelocityX(theta, absVelocity),
                          getVelocityY(theta, absVelocity)};
}

double getDistanceTraveled(double velocityX, double velocityY) {
    return flightTime(velocityY) * velocityX;
}

double targetPractice(double distanceToTarget, double velocityX,
                      double velocityY) {
    return abs(getDistanceTraveled(velocityX, velocityY) - distanceToTarget);
}

void playTargetPractice() {
    cout << "*** Cannonball game *** \n";
    cout << "Target is between 100 and 1000! \n";
    cout << "You have 10 attempts! \n";
    bool win = false;
    int target = randomWithLimits(100, 1000);
    for (int i = 1; i <= 10; i++) {
        cout << "\nAttempt: " << i << endl;
        double theta = getUserInputTheta();
        double absVel = getUserInputAbsVelocity();
        vector<double> vel = getVelocityVector(theta, absVel);
        double error = targetPractice(target, vel[0], vel[1]);
        double distance = getDistanceTraveled(vel[0], vel[1]);
        cout << "Distance to target: " << error << endl;
        if (distance - target < 0) {
            cout << "Attempt too short!\n";
        } else if (distance - target > 0) {
            cout << "Attempt too far!\n";
        }
        cout << "Flight time: ";
        printTime(flightTime(vel[1]));
        cannonBallViz(target, 1000, vel[0], vel[1], 10);
        if (error < 5) {
            win = true;
            break;
        }
    }
    if (win) {
        cout << TextColor(ColorId::green)
             << "\nYou won!!! Attempt is less then 5 meters from target!\n"
             << TextColor();
    } else {
        cout << TextColor(ColorId::red) << "\nYou lost!!!\n" << TextColor();
    }
    cin.get();
}