
task main()
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
		if (vexRT[Btn5D] == 1) {							//moving lift down
			motor[liftLeft] = -127;							//one of these lifts has to be reversed.... change values if neccessary
			motor[liftRight] = 127;
		}
		else if (vexRT[Btn5U] == 1) {					//moving lift up
			motor[liftLeft] = 127;
			motor[liftRight] = -127;
		}
		else
		{
			motor[liftLeft] = 0;
			motor[liftRight] = 0;
		}


		//To grab the star using Button 6
		if (vexRT[Btn6D] == 1)
		{
			motor[starGrabber] = -70;					//may want to make this faster...
		}
		else if (vexRT[Btn6U] == 1)
		{
			motor[starGrabber] = 70;
		}
		else
		{
			motor[starGrabber] = 0;
		}

	}
}