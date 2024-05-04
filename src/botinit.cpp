#include "main.h"
#include "lemlib/api.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
// drive motors
pros::Motor lF(-19, pros::E_MOTOR_GEARSET_18); // left front motor. port 3, reversed
pros::Motor lM(-20, pros::E_MOTOR_GEARSET_18); // left middle motor. port 14, reversed
pros::Motor lB(-15, pros::E_MOTOR_GEARSET_18); // left back motor. port 12, reversed
pros::Motor rF(13, pros::E_MOTOR_GEARSET_18); // right front motor. port 19
pros::Motor rM(12, pros::E_MOTOR_GEARSET_18); // right middle motor. port 20
pros::Motor rB(16, pros::E_MOTOR_GEARSET_18); // right back motor. port 1

pros::Rotation rot_sensor(13);

// pros::Rotation horizontalEnc(15, true);
// lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -3.7);

pros::MotorGroup leftMotors({lF, lM, lB}); // left motor group
pros::MotorGroup rightMotors({rF, rM, rB});

pros::Motor intake1(18, pros::E_MOTOR_GEARSET_36);
pros::Motor intake2(-14, pros::E_MOTOR_GEARSET_36);
pros::MotorGroup intake({intake1, intake2});
pros::Motor kicker1(22, pros::E_MOTOR_GEARSET_06);
pros::Motor kicker2(-21, pros::E_MOTOR_GEARSET_06);
pros::MotorGroup kicker({kicker1, kicker2});
// pros::Motor hang(12, pros::E_MOTOR_GEARSET_06);

                        pros::ADIDigitalOut pto('C');
pros::ADIDigitalOut vertWing('G');
pros::ADIDigitalOut flapPiston('F'); // ************FIX W/ ADI EXPANDER
// pros::ADIDigitalOut flapRightPiston('F');
pros::ADIDigitalOut hangUp('B');
pros::Imu inertial_sensor(17);
// pros::ADIDigitalOut hang('E');
// pros::ADIDigitalOut laDiabla('C'); //fix port later
// pros::ADIDigitalOut bandRelease('D');


lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              7 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(70, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            32, // derivative gain (kD)
                                            3, // anti windup
                                            1, //1, // small error range, in inches
                                            350, // small error range timeout, in milliseconds
                                            3,//3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            15 // maximum acceleration (slew)
);
//
/*
lemlib::ControllerSettings angularController(3, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             40, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);
*/
// angular motion controller
lemlib::ControllerSettings angularController(3, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             40, // derivative gain (kD)
                                             3, // anti windup
                                             7, // small error range, in degrees
                                             50, // small error range timeout, in milliseconds
                                             9, // large error range, in degrees
                                             250, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// void turnConstants(){
//     angularController.kP = 4;
//     angularController.kD = 30;
//     angularController.smallError = 0;
//     angularController.largeError = 0;
// }
// void defaultConstants(){
//         angularController.kP = 3;
//     angularController.kD = 40;
//     angularController.smallError = 100;
//     angularController.largeError = 500;
// }
// lemlib::ControllerSettings angularController(4, // proportional gain (kP)
//                                              0, // integral gain (kI)
//                                              30, // derivative gain (kD)
//                                              3, // anti windup
//                                              0, // small error range, in degrees
//                                              100, // small error range timeout, in milliseconds
//                                              0, // large error range, in degrees
//                                              500, // large error range timeout, in milliseconds
//                                              0 // maximum acceleration (slew)
// );

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial_sensor // inertial sensor
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);