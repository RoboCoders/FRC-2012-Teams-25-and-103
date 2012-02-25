#ifndef DRIVEBASE_H_
#define DRIVEBASE_H_

#include "WPILib.h"
#include <Math.h>
#include "OI.h"

/********************************************
 * 		
 * 		The robot drives consist of 4 CIM Motors.
 * 		103 has a pneumatic shifter along with a 
 * 		pneumatic brkae.
 * 		
 * 		25 has a servo brake and no shifter.
 * 		
 * 		Both teams are also equipped with two encoders
 * 		to aid autonomous functions of the robot. 
 * 
 *  	This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 * 
********************************************/

class DriveBase {

	OI *controls;

	Jaguar *leftDrive;
	Jaguar *rightDrive;

	Servo *rightBrake;
	Servo *leftBrake;

	Solenoid *shifterOn;
	Solenoid *shifterOff;
	
	Encoder *leftEncoder;
	Encoder *rightEncoder;

public:
	// 103 Only
	DriveBase(OI *ctrls, int leftPWM, int rightPWM, int shiftOnSol, int shiftOffSol, int leftEncoderA, int leftEncoderB, int rightEncoderA, int rightEncoderB);
	// 25 Only
	//DriveBase(OI *ctrls, int leftPWM, int rightPWM, int leftBrakePWM, int rightBrakePWMint, int leftEncoderA, int leftEncoderB, int rightEncoderA, int rightEncoderB);
	void drive103();
	void drive25();
	void doNothing();
	void driveStraight(double speed);
	void setDriveSpeed(double leftSpeed, double rightSpeed);
	void setLeftSpeed(double speed);
	double getLeftSpeed();
	void setRightSpeed(double speed);
	double getRightSpeed();
	int getLeftEncoder();
	int getRightEncoder();
	void resetEncoders();
};

#endif
