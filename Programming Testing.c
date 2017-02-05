#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  sight,          sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  bumper,         sensorTouch)
#pragma config(Sensor, dgtl4,  jump3,          sensorTouch)
#pragma config(Motor,  port10,           leftFrontWheel, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port3,           rightFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port1,           leftBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLeftTop,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeftBottom, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRightTop,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRightBottom, tmotorVex393_MC29, openLoop)

void stopMotors()
{
	motor[leftFrontMotor] = 0;
	motor[leftBackMotor] = 0;
	motor[rightFrontMotor] = 0;
	motor[rightBackMotor] = 0;
}


void move(char direction, float time, bool useBumper)
{
	switch (direction)
	{
	case 'F':
	  motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
	  break;
	case 'B':
	  motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	  break;
	case 'R':
	  motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	  break;
	case 'L':
	  motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
	  break;
	default:
	  return;
	}

	int countRunTimeMsec = 0;
	if (useBumper) // use bumper if 0 is passed as the time parameter
	{
		// just in case the sensor is never pushed
	 	// 1 means not pushed
		while (SensorValue[bumper] == 1 && countRunTimeMsec < time * 1000.0)
		{
			wait1Msec(10);
			countRunTimeMsec += 10;
		} // stopped because max time exceeded or bumper value is 1
	} // not bumper
	else
	{
		wait1Msec(time * 1000);
	}

	// time parameter finished so stop
	stopMotors();

	// and now wait a second before next function
	wait1Msec(1000);
}


void turn(char direction, int degrees)
{
	SensorType[in1] = sensorNone;
	wait1Msec(50);
	SensorType[in1] = sensorGyro;
	wait1Msec(1000); 																// robotC calibrates sensor
	switch (direction)
	{
	case 'R':
		motor[leftFrontMotor] = 127;
	  motor[leftBackMotor] = 127;
	  motor[rightFrontMotor] = 127;
	  motor[rightBackMotor] = 127;
	case 'L':
		motor[leftFrontMotor] = -127;
	  motor[leftBackMotor] = -127;
	  motor[rightFrontMotor] = -127;
	  motor[rightBackMotor] = -127;
	default:
		return;
	}
	waitUntil(SensorValue[in1] > degrees * 10);
	stopMotors();
}



//------------------------------------      Control Lift Motors     --------------------------------
void putUpLift()
{
	motor[liftLeftTop] = 127;
	motor[liftLeftBottom] = 127;
	motor[liftRightTop] = -127;
	motor[liftRightBottom] = -127;
	wait1Msec(1350);																//change time for actual robot
	motor[liftLeftTop] = 0;
	motor[liftLeftBottom] = 0;
	motor[liftRightTop] = 0;
	motor[liftRightBottom] = 0;
}


void putDownLift()
{
	motor[liftLeftTop] = -127;
	motor[liftLeftBottom] = -127;
	motor[liftRightTop] = 127;
	motor[liftRightBottom] = 127;
	wait1Msec(1350);																//change time for actual robot
	motor[liftLeftTop] = 0;
	motor[liftLeftBottom] = 0;
	motor[liftRightTop] = 0;
	motor[liftRightBottom] = 0;
}

//-----------------------------------		Sensors			-------------------------------


//to detect an object near them
//ASK WHERE AND HOW THE SONIC-SENSOR IS PLACES
int toSee()					//0 to 255 in cm
{
	return SensorValue(sight);
}

//*******************************************************************************************************************************
	// 															 AUTONOMOUS
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//		HARD CODING FOR 15 SEC AUTONOMOUS, SENSORS FOR 60 SECOND PROGRAMMING SKILLS CHALLENGE
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 /*----------------------Motor Pushing Stars Off Mid------------------------ [Inventor: Christopher 'Lo]*/
void auto(int time) {
	int runningTime = 0;
	const int POWER = 30;
	while (runningTime <= time * 1000)

{
		motor[liftLeftBottom] = POWER;
		motor[liftLeftTop] = POWER;
		motor[liftRightBottom] = POWER;
		motor[liftRightTop] = POWER;

		wait1Msec(100);
		runningTime += 100;

		motor[liftLeftBottom] = -1 * POWER;
		motor[liftLeftTop] = -1 * POWER;
		motor[liftRightBottom] = -1 * POWER;
		motor[liftRightTop] = -1 * POWER;

		wait1Msec(100);
		runningTime += 100;
	}
}

task main()
{
	auto(15);
}
