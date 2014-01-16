#include "WPILib.h"


class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Encoder digEncoder;
	AnalogChannel ultra;
	Servo servo;

public:
	RobotDemo(void):		//Init in same order as listed above
		myRobot(8,1, 1, 1),
		stick(1),
		digEncoder(13, 14),
		ultra(1, 1),
		servo(1, 2)
	{											
		myRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		myRobot.SetSafetyEnabled(false);
		myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
		Wait(2.0); 				//    for 2 seconds
		myRobot.Drive(0.0, 0.0); 	// stop robot
	}


	void OperatorControl(void)
	{
		myRobot.SetSafetyEnabled(true);
		digEncoder.Start();
		const double ppsTOrpm = 60.0/250.0;	// Changed from 250 to 360- 1/13/14. //This converts from Pos per Second to Rotations per Minute (See back of encoder to replace 250 if you need it)
		//ultrasonic1.SetAutomaticMode(true);
		//ultra.SetAverageBits(12);
		const float VoltsToIn = 40.0; // Convert from volts to cm by multiplication (volts from ultrasonic)
		
		while (IsOperatorControl())
		{
			//myRobot.TankDrive(10,10);
			SmartDashboard::PutNumber("Digital Encoder RPM", digEncoder.GetRate()*ppsTOrpm);
			SmartDashboard::PutNumber("Ultrasonic Distance cm", (double) ultra.GetAverageVoltage()*VoltsToIn);
			/*if (stick.GetRawButton(1)) {
				servo.Set(0.0);
			} else {
				servo.Set(1.0);
			}*/
			Wait(0.1);
		}
		digEncoder.Stop();
		//ultrasonic1.SetAutomaticMode(false);
	}
	
	
	/**
	 * Runs during test mode
	 */
	void Test() {
			
	}
};

START_ROBOT_CLASS(RobotDemo);

