#ifndef BALLLIFT_H_
#define BALLLIFT_H_

#include "WPILib.h"
#include <Math.h>

/********************************************
 * 		
 * 		The ball lift consists of two sections
 * 		of belt driven lifts. They use two motors
 * 		independently.
 * 
 *  	This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 * 
********************************************/

class BallLift {

	Victor *bottomBallLift;
	Victor *topBallLift;

	Solenoid *ballDiverterOn;
	Solenoid *ballDiverterOff;

	OI *controls;

public:

	BallLift(OI *ctrls, int bottomPWM, int topPWM, int diverterOnSol, int diverterOffSol);
	void enableLiftControls();
	void enableDiverter();
	void doNothing();
	void setTopLiftSpeed(double speed);
	void setBottomLiftSpeed(double speed);
};

#endif
