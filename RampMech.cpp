#include "WPILib.h"
#include <Math.h>
#include "OI.h"
#include "RampMech.h"

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

RampMech::RampMech(OI *ctrls, int downSol, int upSol) {
	controls = ctrls;

	rampMechDown = new Solenoid(downSol);
	rampMechUp = new Solenoid(upSol);
}

/**
 * Enables controls for the ramp mechanism.
 */
void RampMech:: enableRampMech(){
	// Ramp Basket Thinger code
	if(controls->getLeftButton(3)){	// UP
		rampMechDown->Set(true);
		rampMechUp->Set(false);
	} else if(controls->getLeftButton(2)){ // DOWN
		rampMechDown->Set(false);
		rampMechUp->Set(true);
	}
}

void RampMech::putRampMechDown() {
	rampMechDown->Set(false);
	rampMechUp->Set(true);
}

void RampMech::putRampMechUp() {
	rampMechDown->Set(true);
	rampMechUp->Set(false);
}

