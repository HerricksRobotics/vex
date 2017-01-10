#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  sight,          sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  bumper,         sensorTouch)
#pragma config(Sensor, dgtl4,  jump3,          sensorTouch)
#pragma config(Motor,  port1,           leftFrontMotor, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port3,           leftBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeftTop,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftLeftBottom, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRightTop,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           liftRightBottom, tmotorVex393_MC29, openLoop)


//*******************************************************************************************************************


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

//********************************************************************************************************************

task main()
{
	// 3 preloaded stars, 2 preloaded cubes-- go back to starting box to load objects
	//ROBOT WILL FACE ITS BACK TOWARDS THE FENCE AS ITS STARTING POSITION!

	putUpLift();
	// waitUntil(SensorValue(sight) < 6);				//change the value for the sights to stop the robot to shoot over the fence


	float timeToMid = 6; // make longer than actual time that it takes. This is just in case the robot never triggers the bumper!!!
	float timeToStart = 4;
	move('F', timeToMid, true); // move for 4 sec (or however long it takes) to the fence



	move('B', timeToStart, false);
	wait1Msec(1000); // wait 1 second to load star/cube
	closeGrabber();
	move('F', timeToMid, true);
	openGrabber();

	// load cube, heavier than star --> needs more power to lift
	move('B', timeToStart, false);
	wait1Msec(1000); // wait 1 second to load star/cube
	closeGrabber();
	// lift here
	move('F', timeToMid, true);
	openGrabber();

	// add more to fill 60 seconds


}
