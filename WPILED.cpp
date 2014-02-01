#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
int PutColor(int numLEDs, long color);

class RobotDemo : public SimpleRobot
{
	DigitalOutput clock;
	DigitalOutput data;
public:
	RobotDemo(void):
		clock(2, 8),
		data(2, 9)
	{
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		
	}


	/*
	  Runs the motors with arcade steering. 
	 */
	
	void OperatorControl(void)
	{
		
		while (IsOperatorControl())
		{
			PutColor(80, 0xFF0000);
			Wait(0.1); 
		}
	}
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		
	}
	
	void ampWatch () {
		return;
	}
	
	
	float abs(float num){
		if (num < 0) {
			return (-num);
		} else {
			return (num);
		}
	}
	
	int PutColor(int numLEDs, long color)
	{
		for (int i=0; i<numLEDs; i++)
		{
			for (int j=0; j<24; j++)
			{
				clock.Set(0);
				data.Set(((color & (1 << j)) >> j));
				clock.Set(1);
			}
		}
		clock.Set(0);
		Wait(0.2);
		//while (true)
		//{
			//clock.Set(1);
			//clock.Set(0);
		//}

		return 0;
	}
};

START_ROBOT_CLASS(RobotDemo);


