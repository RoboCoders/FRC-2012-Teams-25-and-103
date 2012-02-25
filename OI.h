#ifndef OI_H_
#define OI_H_

#include "WPILib.h"
#include <Math.h>


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

class OI {
	
	Joystick *leftStick;
	Joystick *rightStick;
	Joystick *operatorStick;

public:
	OI(int leftPort, int rightPort, int opPort);
	double getRightY();
	double getLeftY();
	bool getRightButton(int buttonNum);
	bool getOpButton(int buttonNum);
	bool getLeftButton(int buttonNum);
	double getOpThrottle();
	double getOpX();
};

#endif
