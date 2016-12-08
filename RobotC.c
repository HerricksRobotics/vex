#pragma config(Sensor, dgtl1,  grabberTouch,   sensorTouch)
#pragma config(Sensor, dgtl2,  sight,          sensorSONAR_cm)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftLeft,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           liftRight,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           starGrabber,   tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           hookLift,      tmotorVex393TurboSpeed_MC29, openLoop)

//Caitlin wrote 99% of this class. Rich only made 1% of changes to this class.

/*---------------------------------------------------------------------------*/

#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts



	//I may have to do something about this preset...
	motor[starGrabber] = -50;


}


//*******************************************************************************************************************************



//                                   *********** ACTIONS METHODS *************
//----------------------------------        Movement of the Robot           ----------------------------------------------
void goBackward()
{
	motor[leftMotor] = 127;
	motor[rightMotor] = -127;
}

void goForward()
{
	motor[leftMotor] = -127;
	motor[rightMotor] = 127;
}


void goLeft(float time)
{
	motor[leftMotor] = -127;
	motor[rightMotor] = -127;
	wait1Msec(time * 1000);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}


void goRight(float time)
{
	if (time <= 0) {
	}
	else
	{
		motor[leftMotor] = 127;
		motor[rightMotor] = 127;
		wait1Msec(time * 1000);
		motor[leftMotor] = 0;
		motor[rightMotor] = 0;
	}
}

void stopMotors()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}


//------------------------------------      Control Lift Motors     --------------------------------
void putUpLift()
{
	motor[liftLeft] = 127;
	motor[liftRight] = -127;
	wait1Msec(1350);
	motor[liftLeft] = 0;
	motor[liftRight] = 0;
}


void putDownLift()
{
	motor[liftLeft] = -127;
	motor[liftRight] = 127;
	wait1Msec(740);
	motor[liftLeft] = 0;
	motor[liftRight] = 0;
}

void stopLift()
{
	motor[liftLeft] = 0;
	motor[liftRight] = 0;
}


//------------------------------------      StarGrabber         -------------------------------------
void openStarGrabber()
{
	motor[starGrabber] = 0;         //CHANGE 0 TO A VALUE
	wait1Msec(250);
	motor[starGrabber] = 0;
}

void closeStarGrabber()
{
	motor[starGrabber] = 0;         //CHANGE 0 TO A VALUE
	wait1Msec(150);
	motor[starGrabber] = 0;
}

//-----------------------------------		Sensors			-------------------------------


//*******************************************************************************************************
//		WE MAY NOT NEED THIS. IF WE HAVE TIME, WE COULD HARD-CODE THE NUMBERS FOR PRECISE MEASUREMENTS!
//*******************************************************************************************************


//to detect an object near them
//ASK WHERE AND HOW THE SONIC-SENSOR IS PLACES
int toSee()					//0 to 255 in cm
{
	return SensorValue(sight);

}

//to detect if an object is in the starGrabber
//0 if not pressed
//1 if pressed
long toGrab()
{
	return SensorValue(grabberTouch);
}

//*******************************************************************************************************************************


task autonomous()
{
	float time = 2.8;													//change time to turn 90 degrees


	//when star is in the grabber
	goForward();
	// waitUntil doesn't work even though it should: http://help.robotc.net/WebHelpVEX/Content/Resources/topics/VEX_IQ/Graphical/Program_Flow/waitUntil.htm
	// waitUntil(SensorValue(sight) > 6);				//change the value for the sights to stop the robot to shoot over the fence
	putUpLift();
	wait1Msec(4000);

	putDownLift();


	//to knock off the stars off the fence             NEEDS TO BE CALCULATED TO PRECISE ANGLES
	//goRight();          //find the exact time required to rotate the robot
	//also, the turn might vary on the starting position of the robot

	goForward();

	for(int i=0; i < 10; i++)
	{
		putUpLift();
		putDownLift();
	}
	stopMotors();

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}


//*******************************************************************************************************************************


task usercontrol()
{
	while (true)
	{
		//To control the left side using channel 3
		if (vexRT[Ch3] != 0)
		{
			motor[leftMotor] = vexRT[Ch3] / 10;							//dividing it by 10 to maintain smooth, continuous control
		}
		else
		{
			motor[leftMotor] = 0;
		}


		//To control the right side using channel 2
		if (vexRT[Ch2] != 0)
		{
			motor[rightMotor] = vexRT[Ch2] / 10;					//dividing it by 10 to maintain smooth, continuous control

		}
		else
		{
			motor[rightMotor] = 0;
		}


		//lift using Button 5
		if (vexRT[Btn5D] == 1) {
			motor[liftLeft] = -127;
			motor[liftRight] = 127;
		}
		else if (vexRT[Btn5U] == 1) {
			motor[liftLeft] = 127;
			motor[liftRight] = -127;
		}
		else
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}


		//To grab the star using Button 6
		if (vexRT[Btn6D] == 1) {
			motor[starGrabber] = -70;
		}
		else if (vexRT[Btn6U] == 1) {
			motor[starGrabber] = 70;
		}
		else {
			motor[starGrabber] = 0;
		}

		//idle... To give hardware time to catch up
		wait1Msec(30);
		motor[liftLeft] = 0;
		motor[liftRight] = 0;
		UserControlCodePlaceholderForTesting();
	}
}
