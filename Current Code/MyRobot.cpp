#include "WPILib.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Encoder digEncoder;
	AnalogChannel ultra;

public:
	RobotDemo(void):
		myRobot(8, 1, 9, 2),
		stick(1),
		digEncoder(13, 14),
		ultra(1, 1)
	{											
		myRobot.SetExpiration(0.1);
		myRobot.SetInvertedMotor(myRobot.kFrontRightMotor, true);
		//myRobot.SetInvertedMotor(myRobot.kFrontLeftMotor, true);
		myRobot.SetInvertedMotor(myRobot.kRearRightMotor, true);
		//myRobot.SetInvertedMotor(myRobot.kRearLeftMotor, true);
		
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
		myRobot.SetSafetyEnabled(false);
	}


	/*
	  Runs the motors with arcade steering. 
	 */
	
	void OperatorControl(void)
	{
		NetTest();
		return;
		myRobot.SetSafetyEnabled(true);
		digEncoder.Start();
		const double ppsTOrpm = 60.0/250.0;   //Convert from Pos per Second to Rotations per Minute by multiplication
                                              // (See the second number on the back of the encoder to replace 250 for different encoders)
        const float VoltsToIn = 41.0;         // Convert from volts to cm by multiplication (volts from ultrasonic).
                                              // This value worked for distances between 1' and 10'.
		
		while (IsOperatorControl())
		{
			if (stick.GetRawButton(4)) {
				myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), -1);
			} 
			else if (stick.GetRawButton(5))
			{
				myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), 1);
			}
			else 
			{
				myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), 0);
			}
			
			myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), 0);
			
			SmartDashboard::PutNumber("Digital Encoder RPM", abs(digEncoder.GetRate()*ppsTOrpm));
			SmartDashboard::PutNumber("Ultrasonic Distance inch", (double) ultra.GetAverageVoltage()*VoltsPerInch);
			SmartDashboard::PutNumber("Ultrasonic Voltage", (double) ultra.GetAverageVoltage());

			Wait(0.1);
		}
		digEncoder.Stop();
	}
	
	void NetTest() {
		// Network testing
		// learned from github.com/jacob9706/HighTekerz2012/
		// and Beej's Networking Guide
		struct sockaddr_in serverAddr;
		struct sockaddr_in clientAddr;
		int sockAddrSize;
		int sockFd;
			
		SmartDashboard::PutString("Data Recvd", "initializing");
		sockAddrSize = sizeof(struct sockaddr_in);
		bzero((char *) &serverAddr, sockAddrSize);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_len = (u_char) sockAddrSize;
		serverAddr.sin_port = htons(1140);
		serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
		if ((sockFd = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR) {
			perror("Socket");
			SmartDashboard::PutString("Data Recvd", "socket error");
			return;
		}
			
		if (bind(sockFd, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR) {
			perror("bind");
			SmartDashboard::PutString("Data Recvd", "bind error");
			return;
		}
		
		SmartDashboard::PutString("Data Recvd", "waiting...");
		int bytesRecvd = 0;
		char buf[256];
		while (IsOperatorControl()) {
			memset(buf, 0, sizeof(buf));
			if ((bytesRecvd = recvfrom(sockFd, buf, 255, 0, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR) {
				perror("recv");
				SmartDashboard::PutString("Data Recvd", "recv");
				break;
			}
			SmartDashboard::PutString("Data Recvd", buf);
			
		}
		
		SmartDashboard::PutString("Data Recvd", "Done");
		close(sockFd);
}
	
	
	/**
	 * Runs during test mode
	 */
	void Test() {
		
	}
	
	
	float abs(float num){
		if (num < 0) {
			return (-num);
		} else {
			return (num);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);

