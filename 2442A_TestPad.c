/**
Drives for a distance and proportionally decreases motor power:
@param ticks - distance in encoder ticks
- If ticks < 0 => reverse
- If ticks > 0 => forwards
*/
void driveProp(int ticks)
{
	initEn();
	const int MAX_PWR = 127 * sgn(ticks);

	int distR = ticks; // distance to travel (right)
	int distL = ticks; // distance to travel (left)

	/*
	While the robot has not reached its destination:
	- update loop variables
	- proportionally decrease motor power
	*/
	do
	{
		distR = ticks - SensorValue[rightQuad]; // update right distance
		setRightMotors((int) (distR/ticks) * MAX_PWR * DRIVE_CONV_R); // update right motors
		distL = ticks - SensorValue[leftQuad]; // update left distance
		setLeftMotors((int) (distL/ticks) * MAX_PWR * DRIVE_CONV_L); // update left motors
	}
	while (fabs(distR) > DRIVE_EN && fabs(distL) > DRIVE_EN);

	setAllDriveMotors(0); // clean
}

/**
Turns the robot by a number of ticks and proportionally decreases motor power
@param ticks - number of ticks to turn
- If ticks < 0 => turn left
- If ticks > 0 => turn right
*/
void turnProp(int ticks)
{
	initEn();
	int dist = ticks; // distance
	bool atDestination = fabs(dist) <= DRIVE_EN; // state whether or not robot has reached destination

	/*
	While the robot has not reached its destination
	- update loop variables
	- proportionally decrease motor powers
	*/
	do
	{
		if (sgn(ticks) == -1) { // if turning left => update right motors
			setRightMotors((int) ((dist/ticks) * 127 * DRIVE_CONV_R));
			dist = ticks - SensorValue[rightQuad]; // update distance with right quad
		}
		else { // if turning right => update left motors
			setLeftMotors((int) ((dist/ticks) * 127 * DRIVE_CONV_L));
			dist = ticks - SensorValue[leftQuad]; // update distance with left quad
		}

		atDestination = fabs(dist) <= (float) DRIVE_EN; // update reached state
	}
	while (!atDestination);

	setAllDriveMotors(0); // clean
}

/**
Sets mobile base lift to a position while proportionally decreasing motor power as lift reaches desired position
@param liftPos - a position
*/
void setMobileBaseLiftToPos(int liftPos)
{

}

/**
Drives for some distance but also moves mobile base lift in and out and the same time
Main use in autonomous/programming skills because it may cut down time
@param ticks - distance for drive encoders in ticks
@param MBL_stop - stop point for moving the lift in/out of the way
*/
void driveAndMoveMBL(int ticks, int MBL_stop)
{
}
