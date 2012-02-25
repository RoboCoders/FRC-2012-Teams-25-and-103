#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "WPILib.h"
#include <Math.h>

/********************************************
 * 		
 * 		The shooter consists of two motors on the
 * 		shooting wheel and one motor for the pan.
 * 		Its movement is limited and controled by
 * 		a potentiometer on the pan.
 * 
 * 
 *  	This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 * 
********************************************/

class Shooter {

	OI *controls;

	Victor *shooterWheel;
	Victor *shooterTurret;

	Solenoid *shooterHoodOn;
	Solenoid *shooterHoodOff;

	AnalogChannel *shooterPanPot;

	DriverStationLCD *dsLCD;

public:
	Shooter(OI *ctrls, int wheelPWM, int turretPWM, int hoodOnSol, int hoodOffSol, int panPotChan);
	void enableHoodControls();
	void putHoodUp();
	void enableWheelControls();
	void setShooterSpeed(double speed);
	void enableTurretControls();
	void setTurretSpeed(double speed);
	int getShooterPot();
	void doNothing();
//	int getXForLowestY();
};

#endif
