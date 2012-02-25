#include "WPILib.h"
#include <Math.h>
#include "OI.h"
#include "DriveBase.h"
#include "RampMech.h"
#include "BallLift.h"
#include "Shooter.h"
#include "constants.h"
//#include "Vision/RGBImage.h"
//#include "Vision/BinaryImage.h"

/**
 * This code is for use by teams 103 and 25.
 * 
 * This file contains all the functions to start the robot program such as
 * Autonomous and Teleoperated Controls. 
 * 
 * Before compiling and deploying, make sure you are using the right version. 
 * Check: 
 * 		constants.h
 * 		Shooter.h, Shooter.cpp (constructor and PAN_POT_MIN PAN_POT_MAX) to verify.
 * 		DriveBase.cpp (constructor)
 * 		DriveBase.h (constructor)
 * 		MyRobot.cpp (In teleop, call the correct drive function)
 * 		
 * 		
 * 		This project is copyrighted by Bharat Nain,
 *		Kristian Calhoun and Alexa Stott. Replication 
 *		without written permission is forbidden. It is 
 * 		posted purely for educational purposes and for 
 * 		future reference.
 */ 
class RobotDemo : public SimpleRobot
{
	Relay *airCompressor;
	DigitalInput *pressureSwitch;

	OI *controls;
	DriveBase *drives;
	RampMech *rampThinger;
	BallLift *ballLift;
	Shooter *shooter;

	DriverStationLCD *dsLCD; 
	DriverStation *driverStation;

public:
	RobotDemo(void)
	{
		// CONSTANTS ARE DECLARED IN CONSTANTS.H
		// BEFORE COMPILING, MAKE SURE YOU ARE USING THE RIGHT
		// CONSTANTS FOR YOUR TEAM
		controls = new OI(LEFT_STICK_PORT, RIGHT_STICK_PORT, OP_STICK_PORT);

		// FOR 103 ONLY
		drives = new DriveBase(controls, LEFT_DRIVE_PWM, RIGHT_DRIVE_PWM, 
				SHIFT_ON_SOL, SHIFT_OFF_SOL, LEFT_ENCODER_A_CHAN, LEFT_ENCODER_B_CHAN,
				RIGHT_ENCODER_A_CHAN, RIGHT_ENCODER_B_CHAN);

		// FOR 25 ONLY
		/*drives = new DriveBase(controls, LEFT_DRIVE_PWM, RIGHT_DRIVE_PWM,
					LEFT_BRAKE_PWM, RIGHT_BRAKE_PWM, LEFT_ENCODER_A_CHAN, LEFT_ENCODER_B_CHAN,
					RIGHT_ENCODER_A_CHAN, RIGHT_ENCODER_B_CHAN);*/

		// Set up and initialize camera
		/*AxisCamera &camera = AxisCamera::GetInstance();

		printf("Setting camera parameters\n");
		camera.WriteResolution(AxisCamera::kResolution_320x240);
		camera.WriteCompression(20);
		camera.WriteBrightness(10);
		camera.WriteColorLevel(100);
		camera.WriteMaxFPS(10);*/

		rampThinger = new RampMech(controls, RAMP_DOWN_SOL, RAMP_UP_SOL);

		ballLift = new BallLift(controls, LIFT_BOT_PWM, LIFT_TOP_PWM, 
				DIVERT_ON_SOL, DIVERT_OFF_SOL);

		shooter = new Shooter(controls, WHEEL_PWM, TURRET_PWM, 
				HOOD_ON_SOL, HOOD_OFF_SOL, PAN_POT_CHAN);

		airCompressor = new Relay(1, Relay::kForwardOnly);
		pressureSwitch = new DigitalInput(14);	

		dsLCD = DriverStationLCD::GetInstance();

		driverStation = DriverStation::GetInstance();

		GetWatchdog().SetEnabled(false);
	}

	/**
	 * 
	 */

	void Autonomous(void)
	{			
		//autonomousMode->run(1);
		int selectedAuto = getSelectedAuto();
		float primaryDelay = getDelay(1);
		Timer *time = new Timer();
		while(IsAutonomous() && IsEnabled())
		{
			
		}
	}

	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(false);
		while(IsOperatorControl() && IsEnabled())
		{
			// Pneumatics
			if(pressureSwitch->Get() == 1){
				airCompressor->Set(Relay::kOff);
			} else {
				airCompressor->Set(Relay::kOn);
			}

			drives->drive103();		//drives with shifter
			//drives->drive25();			//drives with brakes

			ballLift->enableLiftControls();
			ballLift->enableDiverter();

			shooter->enableHoodControls();
			shooter->enableWheelControls();
			shooter->enableTurretControls();

			rampThinger->enableRampMech();     

			// Hack to reset encoders
			if(controls->getLeftButton(11)) {
				drives->resetEncoders();
			}

			if(driverStation->GetDigitalIn(1)){
				dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "DIGITAL IN ONE IS ON");
			} else {
				dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "DIGITAL IN ONE IS OFF");
			}
			
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "PRES SW: %d", pressureSwitch->Get());

			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Pot: %d", shooter->getShooterPot());
			//dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Left Enc %d      ", drives->getLeftEncoder());
			//dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Right Enc %d     ", drives->getRightEncoder());
			dsLCD->UpdateLCD();
			GetWatchdog().SetEnabled(false);
		}
	}

	int getSelectedAuto(){
		for(int i = 1; i <= 8; i++){
			if(driverStation->GetDigitalIn(i)){
				return i;
			}
		}
		return 1;
	}

	float getDelay(int delayType){
		if(delayType == 1){
			return driverStation->GetAnalogIn(1) + driverStation->GetAnalogIn(2);
		} else if(delayType == 2){
			return driverStation->GetAnalogIn(3) + driverStation->GetAnalogIn(4);
		} else {
			return 0;
		}
	}

};

START_ROBOT_CLASS(RobotDemo);
