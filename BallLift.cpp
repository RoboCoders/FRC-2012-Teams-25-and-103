#include "WPILib.h"
#include <Math.h>
#include "OI.h"
#include "BallLift.h"

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

BallLift::BallLift(OI *ctrls, int bottomPWM, int topPWM, int diverterOnSol, int diverterOffSol) {
	bottomBallLift = new Victor(bottomPWM);
	topBallLift = new Victor(topPWM);

	ballDiverterOn = new Solenoid(diverterOnSol);
	ballDiverterOff = new Solenoid(diverterOffSol);

	controls = ctrls;
}

/**
 * Enables controls for the top and bottom ball lift.
 */
void BallLift::enableLiftControls(){
	// Bottom ball Lift controls
	if(controls->getOpButton(6)){ 			// Spit balls out
		bottomBallLift->Set(1.0);
	} else if(controls->getOpButton(7)){ 	// Pick balls up
		bottomBallLift->Set(-1.0);
	} else{
		bottomBallLift->Set(0.0);
	}

	//Top Ball Lift Controls
	if(controls->getOpButton(11)){
		topBallLift->Set(1.0);
	} else if(controls->getOpButton(10)){
		topBallLift->Set(-1.0);
	} else {
		topBallLift->Set(0.0);
	}
}

/**
 * Enables controls for the ball diverter.
 */
void BallLift::enableDiverter(){
	if(controls->getOpButton(8))
	{
		ballDiverterOn->Set(true);
		ballDiverterOff->Set(false);
	} else if(controls->getOpButton(9)){
		ballDiverterOn->Set(false);
		ballDiverterOff->Set(true);
	}
}

void BallLift::doNothing(){
	bottomBallLift->Set(0.0);
	topBallLift->Set(0.0);
}

void BallLift::setTopLiftSpeed(double speed){
	topBallLift->Set(speed);
}

void BallLift::setBottomLiftSpeed(double speed){
	bottomBallLift->Set(speed);
}

