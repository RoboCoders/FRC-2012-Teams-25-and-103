#include "WPILib.h"
#include <Math.h>
#include "OI.h"

/********************************************
 * 		
 * 		Functions on the operator board. Current
 * 		this includes two driver joysticks (tank drive)
 * 		and one operator joystick.
 * 
 * 
 *  	This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 * 
********************************************/

OI::OI(int leftPort, int rightPort, int opPort){
	leftStick = new Joystick(leftPort);
	rightStick = new Joystick(rightPort);
	operatorStick = new Joystick(opPort);
}

/**
 * Returns the Y value of the right joystick.
 */
double OI::getRightY(){
	return rightStick->GetY();
}

/**
 * Returns the Y value of the left joystick.
 */
double OI::getLeftY(){
	return leftStick->GetY();
}

/**
 * Returns the state of the specified button
 * on the right joystick.
 */
bool OI::getRightButton(int buttonNum){
	return rightStick->GetRawButton(buttonNum);
}

/**
 * Returns the state of the specified button
 * on the operator joystick.
 */
bool OI::getOpButton(int buttonNum){
	return operatorStick->GetRawButton(buttonNum);
}

/**
 * Returns the state of the specified button
 * on the left joystick.
 */
bool OI::getLeftButton(int buttonNum){
	return leftStick->GetRawButton(buttonNum);
}

/**
 * Returns the throttle of the operator joystick.
 */
double OI::getOpThrottle(){
	return operatorStick->GetThrottle();
}

/**
 * Returns the X value of the operator joystick.
 */
double OI::getOpX(){
	return operatorStick->GetX();
}



