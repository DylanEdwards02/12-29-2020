#include "main.h"

//Intake Motors
pros::Motor intakeL(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS); //Dont Know as of 12/2
pros::Motor intakeR(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS); //Dont Know as of 12/2
pros::Motor frontRollers(16, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor backRoller(15, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
//Drive Motors
pros::Motor DriveRightBack(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveRightFront(13, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveLeftBack(19, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor DriveLeftFront(14, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);


//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//************************************
//Sensors
//************************************

//Optical Sensors
pros::Optical TopOptical (5);
pros::Optical LowerOptical (7);
pros::Distance TopDistance (6);

//Rotation Sensors
//pros::Rotation DREncoder (16); Currently not in use
//pros::Rotation DLEncoder (11); Currently not in use
//pros::Rotation DBEncoder (8); Currently not in use

//Line Followers
//pros::ADILineSensor LineSensorTop('A'); Currently not in use
//pros::ADILineSensor LineSensorMiddle('B'); Currently not in use

//Bump Switches
//pros::ADIDigitalIn button ('A');
