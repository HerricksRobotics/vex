#pragma config(Motor,  port1,           leftWheel,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightWheel,    tmotorVex393_MC29, openLoop)


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
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  int leftSpeed;
	int rightSpeed;

	while (true)
	{
		//To control the left side using channel 3
		if (vexRT[Ch3] > -35 && vexRT[Ch3] < 35)
		{
			leftSpeed = 0;
		}
		else
		{
			leftSpeed = vexRT[Ch3];
		}


		//To control the right side using channel 2
		if (vexRT[Ch2] > -35 && vexRT[Ch2] < 35)
		{
			rightSpeed = 0;
		}
		else
		{
			rightSpeed = vexRT[Ch2];
		}

		motor[leftWheel] = leftSpeed;
		motor[rightWheel] = -rightSpeed;

	}
}
