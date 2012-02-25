#ifndef RAMPMECH_H_
#define RAMPMECH_H_

#include "WPILib.h"
#include <Math.h>


/********************************************
 * 		
 * 		The ramp mechanism helps the robot bring the 
 * 		ramp down via pneumatics.
 * 
 * 
 *  	This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 * 
********************************************/

class RampMech {

	OI *controls;

	Solenoid *rampMechDown;
	Solenoid *rampMechUp;

public:
	RampMech(OI *ctrls, int downSol, int upSol);
	void enableRampMech();
	void putRampMechDown();
	void putRampMechUp();
};

#endif
