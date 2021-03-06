#pragma config(Sensor, in1,    xAccel,         sensorAccelerometer)
#pragma config(Sensor, in2,    yAccel,         sensorAccelerometer)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////
// Auton Void
/////
void Auton()
{
	//Universal Integers
	float Kp = 3;
	float Ki = 0.01;
	float Kd = 0.01;
	float powerBackRight;
	float powerFrontRight;
	float powerBackLeft;
	float powerFrontLeft;
	
	//X Integers
	float xBias;
	float xError;
	float xIntegral;
	float yIntegral;
	float xDerivative;
	float xLastError;
	float xMove;
	
	//Y Integer
	float yBias;
	float yError;
	float yDerivative;
	float yLastError;
	float yMove;
	
	wait1Msec(2000);

	/* CALIBRATION START */

	/* Set the bias values */
	xBias = SensorValue(xAccel);
	yBias = SensorValue(yAccel);
	wait1Msec(25);

	/* CALIBRATION  OVER */

	while(true)
	{
		//While robot is accelerating in the X axis, loop this code
		while(currentX > threshold || currentX < threshold - 6)
		{
			xError = SensorValue(xAccel) - xBias;
			xIntegral = xIntegral + xError;
			xDerivative = xError - xLastError;
			xMove = (Kp * xError) + (Ki * xIntegral) + (Kd * xDerivative);
			xLastError = xError;
		}
		
		//If robot is accelerating in the Y axis,loop this code
		while(currentY > threshold || currentY < threshold - 6)
		{
			yError = SensorValue(xAccel) - xBias;
			yIntegral = yIntegral + yError;
			yDerivative = yError - yLastError;
			yMove = (Kp * yError) + (Ki * yIntegral) + (Kd * yDerivative);
			yLastError = yError;
		}	
		
		powerFrontRight = xError - yError;
		powerBackRight = xError + yError;
		powerFrontLeft = xError + yError;
		powerBackRight = xError - yError;
		
		motor[frontRight] = powerFrontRight;
		motor[backRight] = powerBackRight;
		motor[frontLeft] = powerFrontLeft;
		motor[backLeft] = powerBackLeft;
		
	}
}
