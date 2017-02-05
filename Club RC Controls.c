#pragma config(Motor,  port10,           leftFrontWheel, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port3,           rightFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rightBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port1,           leftBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLeftTop,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftLeftBottom, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           liftRightTop,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRightBottom, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{

  int leftSpeed;
 	int rightSpeed;
	int liftSpeed;
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

		motor[leftBackWheel] = leftSpeed;
		motor[leftFrontWheel]= -leftSpeed;
		motor[rightBackWheel] = -rightSpeed;
		motor[rightFrontWheel] = -rightSpeed;

		//lift Down using Button 6D

		if (vexRT[Btn6U] == 1)				//moving lift down
		{
			liftSpeed = -127;
		}
		else
		{
			liftSpeed = 0;
		}


		motor[liftLeftTop] = liftSpeed;
		motor[liftLeftBottom] = -liftSpeed;
		motor[liftRightTop] = -liftSpeed;
		motor[liftRightBottom] = liftSpeed;


		if (vexRT[Btn5U] == 1)				//moving lift up
		{
			liftSpeed = 127;
		}
		else
		{
			liftSpeed = 0;
		}


		motor[liftLeftTop] = liftSpeed;
		motor[liftLeftBottom] = -liftSpeed;
		motor[liftRightTop] = -liftSpeed;
		motor[liftRightBottom] = -liftSpeed;

	}
}
