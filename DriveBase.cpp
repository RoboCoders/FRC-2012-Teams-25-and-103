#include "WPILib.h"
#include <Math.h>
#include "OI.h"
#include "DriveBase.h"

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

/************* FOR 103 ONLY ***************/
DriveBase::DriveBase(OI *ctrls, int leftPWM, int rightPWM, int shiftOnSol, int shiftOffSol, int leftEncoderA, int leftEncoderB, int rightEncoderA, int rightEncoderB) {
	controls = ctrls;

	leftDrive = new Jaguar(leftPWM);
	rightDrive = new Jaguar(rightPWM);

	shifterOn = new Solenoid(shiftOnSol);
	shifterOff = new Solenoid(shiftOffSol);

	leftEncoder = new Encoder(leftEncoderA, leftEncoderB);
	rightEncoder = new Encoder(rightEncoderA, rightEncoderB);
}

/************* FOR 25 ONLY ****************/
/*DriveBase::DriveBase(OI *ctrls, int leftPWM, int rightPWM, int leftBrakePWM, int rightBrakePWM, int leftEncoderA, int leftEncoderB, int rightEncoderA, int rightEncoderB){
		controls = ctrls;

		leftDrive = new Jaguar(leftPWM);
		rightDrive = new Jaguar(rightPWM);

		leftBrake = new Servo(rightBrakePWM);
		rightBrake = new Servo(leftBrakePWM);

		leftEncoder = new Encoder(leftEncoderA, leftEncoderB);
		rightEncoder = new Encoder(rightEncoderA, rightEncoderB);
	}*/

/**
 * Sets up tank drive.
 * Enables shifter controls.
 */
void DriveBase::drive103(){
	leftDrive->Set(controls->getLeftY());
	rightDrive->Set(controls->getRightY());

	if(controls->getRightButton(3)){
		shifterOn->Set(true);
		shifterOff->Set(false);
	} else if(controls->getRightButton(2)){
		shifterOn->Set(false);
		shifterOff->Set(true);
	}

}

/**
 * Sets up tank drive.
 * Enables brake controls
 */
void DriveBase::drive25(){
	leftDrive->Set(controls->getLeftY());
	rightDrive->Set(controls->getRightY());
}

void DriveBase::doNothing(){
	leftDrive->Set(0.0);
	rightDrive->Set(0.0);
}

void DriveBase::driveStraight(double speed) {
	leftDrive->Set(speed);
	rightDrive->Set(speed);
}

void DriveBase::setDriveSpeed(double leftSpeed, double rightSpeed) {
	leftDrive->Set(leftSpeed);
	rightDrive->Set(rightSpeed);
}

void DriveBase::setLeftSpeed(double speed) {
	leftDrive->Set(speed);
}

double DriveBase::getLeftSpeed() {
	return leftDrive->Get();
}

void DriveBase::setRightSpeed(double speed) {
	rightDrive->Set(speed);
}

double DriveBase::getRightSpeed() {
	return rightDrive->Get();
}

int DriveBase::getLeftEncoder() {
	leftEncoder->Start();
	return leftEncoder->GetRaw();
}

int DriveBase::getRightEncoder() {
	rightEncoder->Start();
	return rightEncoder->GetRaw();
}

void DriveBase::resetEncoders() {
	leftEncoder->Reset();
	rightEncoder->Reset();
}
