#include "WPILib.h"
#include <Math.h>
#include "OI.h"
#include "shooter.h"
//#include "Vision/RGBImage.h"
//#include "Vision/BinaryImage.h"


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


// Potentiometer max and min
/************ 103 ONLY ***********/
static const int PAN_POT_MAX = 920, PAN_POT_MIN = 110;

/************ 25 ONLY ************/
//static const int PAN_POT_MAX = 900, PAN_POT_MIN = 100;

Shooter::Shooter(OI *ctrls, int wheelPWM, int turretPWM, int hoodOnSol, int hoodOffSol, int panPotChan){
	controls = ctrls;

	shooterWheel = new Victor(wheelPWM);		
	shooterTurret = new Victor(turretPWM);

	shooterHoodOn = new Solenoid(hoodOnSol);
	shooterHoodOff = new Solenoid(hoodOffSol);

	shooterPanPot = new AnalogChannel(panPotChan);

	dsLCD = DriverStationLCD::GetInstance();
}

/**
 * Enables controls for the shooter hood.
 */
void Shooter::enableHoodControls(){
	if(controls->getOpButton(3)){
		shooterHoodOn->Set(true);
		shooterHoodOff->Set(false);
	} else if(controls->getOpButton(2)){
		shooterHoodOn->Set(false);
		shooterHoodOff->Set(true);
	}
}

void Shooter::putHoodUp() {
	shooterHoodOn->Set(true);
	shooterHoodOff->Set(false);
}

/**
 * Enables controls for the shooter wheel.
 */
void Shooter::enableWheelControls(){
	//Set shooter wheel 
	if(controls->getOpThrottle() > 0){
		float tempSpeed = 0.5 + controls->getOpThrottle()/2;
		//dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "WhlSped: %f", tempSpeed);
		shooterWheel->Set(tempSpeed);
	} else if(controls->getOpThrottle() < 0){
		float tempSpeed = 0.5 + controls->getOpThrottle() / 2;
		//dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "WhlSped: %f", tempSpeed);
		shooterWheel->Set(tempSpeed);
	} else if(controls->getOpThrottle() == 0){
		shooterWheel->Set(0.5);
	} else{
		shooterWheel->Set(0.0);
	}
	dsLCD->UpdateLCD();
}

void Shooter::setShooterSpeed(double speed) {
	shooterWheel->Set(speed);
}

/**
 * Enables controls for the shooter turret.
 * Sets pot limits to prevent breaking shit.
 */
void Shooter::enableTurretControls(){
	// Camera Stuff
	/*if (controls->getOpButton(4)) {
		
		int x = getXForLowestY();
		static const int IMAGE_CENTER = 160; //[320x240 Resolution]
		if (x == -1) {
			setTurretSpeed(0.0);
		} else if ( x > IMAGE_CENTER){
			setTurretSpeed(0.2);
		} else {
			setTurretSpeed(0.0);
		}
		
		// Pot safety for camera control
		if (shooterPanPot->GetValue() < PAN_POT_MIN) {
			setTurretSpeed(0.0);
		} else if (shooterPanPot->GetValue() > PAN_POT_MAX) {
			setTurretSpeed(0.0);
		}

	} else */ 
	if(shooterPanPot->GetValue() > PAN_POT_MAX){
		if(controls->getOpX() > 0.0){
			shooterTurret->Set(controls->getOpX());
		} else {
			shooterTurret->Set(0.0);
		}
	} else if(shooterPanPot->GetValue() < PAN_POT_MIN){
		if(controls->getOpX() < 0.0){
			shooterTurret->Set(controls->getOpX());
		} else {
			shooterTurret->Set(0.0);
		}
	} else {
		shooterTurret->Set(controls->getOpX());
	}
}

void Shooter::setTurretSpeed(double speed) {
	shooterTurret->Set(speed);
}

int Shooter::getShooterPot(){
	return shooterPanPot->GetValue();

}

void Shooter::doNothing(){
	shooterWheel->Set(0.0);
	shooterTurret->Set(0.0);
}
/*
int Shooter::getXForLowestY() {
	
	// Camera tracking
	Threshold threshold(25, 255, 0, 45, 0, 47);
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_BOUNDING_RECT_WIDTH, 30, 400, false, false},
			{IMAQ_MT_BOUNDING_RECT_HEIGHT, 40, 400, false, false}
	};
	AxisCamera &camera = AxisCamera::GetInstance();
	ColorImage *image = camera.GetImage();
	BinaryImage *thresholdImage = image->ThresholdRGB(threshold);	// get just the red target pixels
	BinaryImage *bigObjectsImage = thresholdImage->RemoveSmallObjects(false, 2);  // remove small objects (noise)
	BinaryImage *convexHullImage = bigObjectsImage->ConvexHull(false);  // fill in partial and full rectangles
	BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 2);  // find the rectangles
	vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();  // get the results

	int x = -1;
	int minY = 1000;
	for (unsigned i = 0; i < reports->size(); i++) {
		ParticleAnalysisReport *r = &(reports->at(i));
		//printf("particle: %d  center_mass_x: %d\n", i, r->center_mass_x);
		dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Mid: %d", r->center_mass_x);
		int center_x = (int) r->center_mass_x;
		int center_y = (int) r->center_mass_y;
		if (center_y < minY) {
			minY = center_y;
			x = center_x;
		}		
	}

	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "No find");
	dsLCD->UpdateLCD();

	// be sure to delete images after using them
	delete reports;
	delete filteredImage;
	delete convexHullImage;
	delete bigObjectsImage;
	delete thresholdImage;
	delete image;
	
	return x;
}*/



