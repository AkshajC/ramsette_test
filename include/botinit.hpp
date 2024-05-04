#pragma once
#include "main.h"

void defaultConstants();
void turnConstants();
extern pros::Controller master;
// drive motors
extern pros::Motor lF; // left front motor. port 3, reversed
extern pros::Motor lM; // left middle motor. port 14, reversed
extern pros::Motor lB; // left back motor. port 12, reversed
extern pros::Motor rF; // right front motor. port 19
extern pros::Motor rM; // right middle motor. port 20
extern pros::Motor rB; // right back motor. port 1

extern pros::Rotation rot_sensor;

extern pros::MotorGroup leftMotors; // left motor group
extern pros::MotorGroup rightMotors;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern pros::MotorGroup intake;
extern pros::Motor kicker1;
extern pros::Motor kicker2;
extern pros::MotorGroup kicker;
extern pros::Motor hang;

extern pros::ADIDigitalOut flapPiston; // ************FIX W/ ADI EXPANDER
// extern pros::ADIDigitalOut flapRightPiston;
extern pros::ADIDigitalOut pto;
extern pros::ADIDigitalOut hangUp;
extern pros::ADIDigitalOut vertWing;
extern pros::Imu inertial_sensor;



extern lemlib::Drivetrain drivetrain;

// lateral motion controller
extern lemlib::ControllerSettings linearController;

// angular motion controller
extern lemlib::ControllerSettings angularController;

extern lemlib::OdomSensors sensors;
extern lemlib::Chassis chassis;