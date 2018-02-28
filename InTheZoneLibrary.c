#pragma config(Sensor, in1,    leftClawPoten,  sensorPotentiometer)
#pragma config(Sensor, in2,    liftPoten,      sensorPotentiometer)
#pragma config(Sensor, in3,    rightClawPoten, sensorPotentiometer)
#pragma config(Sensor, in4,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  leftQuad,       sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightQuad,      sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  redLED,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl9,  yellowLED,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, leftPiston,     sensorDigitalOut)
#pragma config(Sensor, dgtl12, rightPiston,    sensorDigitalOut)
#pragma config(Motor,  port1,           claw2,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           test,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           driveLeftFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           driveLeftBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           driveRightFront, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           driveRightBack, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           forklift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          claw,          tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma systemFile

float rightPowerAdjustment = 0;
float leftPowerAdjustment = 0;
float theta = 0;

task correctStraight() //UNUSED METHOD/FOR TESTING GYRO
{
	int adjustedTheta = (int) (theta * 10);
	int err = adjustedTheta;
	int power;
	while(1)
	{
		err = adjustedTheta - SensorValue[gyro];
		power = 127*err*0.0027;
		rightPowerAdjustment = power;
		leftPowerAdjustment = -power;
		writeDebugStreamLine("Err: %d, Power: %d",err,power);
		wait1Msec(50);
	}
}

void setLeftMotors(int power)
{
	motor[driveLeftFront] = power;
	motor[driveLeftBack] = power;
}

void setRightMotors(int power)
{
	motor[driveRightFront] = (int) (power*0.58);
	motor[driveRightBack] = (int) (power*0.58);
}
void setAllDriveMotors(int power)
{
	setLeftMotors(power);
	setRightMotors(power);
}

void setLiftPower(int power)
{
	motor[liftLeft] = power;
	motor[liftRight] = power;
}

void setForkliftPower(int power)
{
	//motor[forklift] = power;
	SensorValue[rightPiston] = power;
	SensorValue[leftPiston]  = power;
}

void setClawPower(int power)
{
	motor[claw] = power;
	motor[claw2] = power;
<<<<<<< HEAD

}

void turnDeg(int angle)
=======

}

void turnDeg(int angle) //TO BE REMOVED AFTER EVERYTHING IS CONVERTED TO TURNTOPOS()
>>>>>>> origin/master
{
	SensorValue[rightQuad] = 0;
	SensorValue[leftQuad] = 0;
	int adjustedAngle = angle*385/360;
	int err = adjustedAngle;
	int power;
	while(abs(err)>20)
	{
		err = adjustedAngle - SensorValue[leftQuad];
		power=-127;
		writeDebugStreamLine("err: %d",err);
		//power = err*127/ajustedAngle + 10;
		setRightMotors(power);
		setLeftMotors(-power);
	}
	setRightMotors(sgn(angle) * -63);
	setLeftMotors(sgn(angle) * 63);
	wait10Msec(3);
	setAllDriveMotors(0);
}

<<<<<<< HEAD
void driveStraight(int dest,float kp, float kbias)
=======
void driveStraightAuton(int dest, int basePower, float rightMultiplier)
>>>>>>> origin/master
{
	SensorValue[leftQuad] = 0;
	int err = dest;
	int power = 127;
	//startTask(correctStraight);
	while(abs(err)>20)
	{
		err = dest - SensorValue[leftQuad];
<<<<<<< HEAD
		//power = (int) (err*127.0/dest*kp + kbias);
		power = 127*kp*sgn(err);
		setAllDriveMotors(power);
=======
		power = basePower*sgn(err);
		setRightMotors((int)(power*rightMultiplier));// + rightPowerAdjustment));
		setLeftMotors((int) (power));//+leftPowerAdjustment));
		//writeDebugStreamLine("RightAdjustment: %d, LeftAdjustment: %d", rightPowerAdjustment, leftPowerAdjustment);
>>>>>>> origin/master
		//writeDebugStreamLine("err: %d, power: %d, kp: %d, kbias: %d, power?:", err, power, kp, kbias, err*127/dest*kp);
	}
	//stopTask(correctStraight);
	setAllDriveMotors(0);
}

void turnToPos(int pos)
{
<<<<<<< HEAD
	SensorValue[leftQuad] = 0;
	int err = dest;
	int power = 127;
	while(abs(err)>20)
	{
		err = dest - SensorValue[leftQuad];
		//power = (int) (err*127.0/dest*kp + kbias);
		power = 127*kp*sgn(err);
		setRightMotors((int)(power*1.1));
		setLeftMotors(power);
		//writeDebugStreamLine("err: %d, power: %d, kp: %d, kbias: %d, power?:", err, power, kp, kbias, err*127/dest*kp);
=======
	int err = pos - SensorValue[gyro];
	int power;
	while(fabs(err) > 50)
	{
		err = pos - SensorValue[gyro];
		power = 127*err*0.004+10;
		setRightMotors(power);
		setLeftMotors(-power);
		writeDebugStreamLine("Err: %d, Power: %d",err,power);
		wait1Msec(50);
>>>>>>> origin/master
	}
}
<<<<<<< HEAD

void actuallyDriveStraight(int time)
{
	clearTimer(T1);
	SensorValue[rightQuad] = 0;
	SensorValue[leftQuad]= 0;
	int masterPower = 100;
	setRightMotors(masterPower);
	setLeftMotors(masterPower);
	int err;
	int adjustedPower;
	int left;
	int right;
	while(time100(T1)<time*10)
	{
		int left = - SensorValue[leftQuad];
		right = SensorValue[rightQuad];
		err = SensorValue[leftQuad] - SensorValue[rightQuad];
		adjustedPower = 0.3*err;
		setRightMotors(masterPower + adjustedPower);

		SensorValue[rightQuad] = 0;
		SensorValue[leftQuad] = 0;

		wait1Msec(50);
	}
}
=======
//void actuallyDriveStraight(int time)
//{
//	clearTimer(T1);
//	SensorValue[rightQuad] = 0;
//	SensorValue[leftQuad]= 0;
//	int masterPower = -100;
//	int adjustedPower =masterPower*1.17;
//	setRightMotors(adjustedPower);
//	setLeftMotors(masterPower);
//	int err;
//	int left;
//	int right;
//	while(time100(T1)<time*10)
//	{
//		int left = SensorValue[leftQuad];
//		right = - SensorValue[rightQuad];
//		err = left - right;
//		adjustedPower += 0.4*err;
//		writeDebugStreamLine("Left Speed: %d, Right Speed: %d, Error: %d, AdjustedPower: %d",left,right,err,adjustedPower);
//		setRightMotors(adjustedPower);

//		SensorValue[rightQuad] = 0;
//		SensorValue[leftQuad] = 0;

//		wait1Msec(50);
//	}
//}
>>>>>>> origin/master
