#pragma config(Sensor, S1,		 frontSensor,		 sensorSONAR)
#pragma config(Sensor, S2,		 leftSensor,		 sensorSONAR)
#pragma config(Sensor, S3,		 soundSensor,		 sensorSoundDB)
#pragma config(Motor,	 motorA,					shooter,			 tmotorNXT, PIDControl, encoder)
#pragma config(Motor,	 motorB,					leftMotor,		 tmotorNXT, PIDControl, encoder)
#pragma config(Motor,	 motorC,					rightMotor,		 tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

/*
ASSUMPTIONS AND EDGE CASES
- Assume no dead ends.
- Assume there is enough room for the robot to move/turn successfully.
- Assume robot can successfully detect all obstacles in the room.
- Assume optimal starting position.
*/

void moveForwards()
{
	motor[leftMotor] = 40;
	motor[rightMotor] = 40;
}

void moveBackwards()
{
	motor[leftMotor] = -40;
	motor[rightMotor] = -40;
}

void stopMove()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}

void turnLeft()
{
	motor[leftMotor] = -20;
	motor[rightMotor] = 20;
	wait1Msec(880);
	stopMove();
	wait1Msec(500);
}

void turnRight()
{
	motor[leftMotor] = 20;
	motor[rightMotor] = -20;
	wait1Msec(880);
	stopMove();
	wait1Msec(500);
}

void nudgeRight()
{
	motor[leftMotor] = 50;
	motor[rightMotor] = 20;
	wait1Msec(100);
	motor[leftMotor] = 20;
	motor[rightMotor] = 30;
	wait1Msec(100);
}

int attackMode(int objDist)
{
	int r = 0;
	clearTimer(T1);
	while(time1[T1]<1500) {
		if(SensorValue[frontSensor] > objDist+5 || SensorValue[frontSensor] < objDist-5) {
			playSound(soundBeepBeep);

			motor[shooter] = 45;
			wait1Msec(500);
			motor[shooter] = 0;
			r = 1;
		}
		else {
			stopMove();
		}
	}
	return r;
}

task main()
{
	while(true)
	{
		if(SensorValue[frontSensor] > 24)
		{
			moveForwards();
			if (SensorValue[leftSensor] < 15) {
				nudgeRight();
				continue;
			}
		}
		else
		{
			stopMove();
			//if (SensorValue[frontSensor] > 24 && SensorValue[leftSensor] <= 8) {
			//	motor[leftMotor] = 20;
			//	motor[rightMotor] = -20;
			//	wait1Msec(200);
			//	motor[leftMotor] = 0;
			//	motor[rightMotor] = 0;
			//	continue;
			//}
			//else {
				wait1Msec(300);
				int objDist = SensorValue[frontSensor];
				if (attackMode(objDist) == 1) {
					continue;
				}
				else {
					if (SensorValue[frontSensor] < 20) {
						moveBackwards();
						wait1Msec(500);
						continue;
					}
					turnRight();
					short rightVal = SensorValue[frontSensor];
					turnLeft();
					if (SensorValue[leftSensor] > rightVal){
						turnLeft();
						continue;
					}
					else
					{
						turnRight();
						continue;
					}
				}
			//}
		}
	}
}
