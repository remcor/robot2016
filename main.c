#pragma config(Motor, port2, seeder, tmotorServoStandard, openLoop)
#pragma config(Motor, port3, leftWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port4, rightWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port5, handLeft, tmotorServoStandard, openLoop)
#pragma config(Motor, port7, handRight, tmotorServoStandard, openLoop)
#pragma config(Motor, port8, handMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port9, armMotor, tmotorVex269_MC29, openLoop)

/******************************************
Joystick mapping:
	Ch3 - Left Joystick up/down
	Ch2 - Right Joystick up/down
Buttons mapping:
	Btn5U - Hand Rotate Left
	Btn6U - Hand Rotate Right
	Btn5D - Raise Arm
	Btn6D - Lower Arm
	Btn7D - Close Seeder
	Btn7U - Open Seeder
	Btn8D - Open Hand
	Btn8U - Closes Hand
******************************************/

task main ()
{
	int maxServoPos = 127;
	int maxServoNeg = -127;
	int servoIncrement = 10;

	int threshold = 10;

	while (true) {

		// If greater then threshold set, otherwise set to 0
		if (vexRT[Ch3] > threshold || vexRT[Ch3] < -threshold) {
			motor[leftWheel] = vexRT[Ch3];   // Left Joystick Y value
		} else {
			motor[leftWheel] = 0;
		}

		// If greater then threshold set, otherwise set to 0
		if (vexRT[Ch2] > threshold || vexRT[Ch2] < -threshold) {
			motor[rightWheel] = vexRT[Ch2];   // Right Joystick Y value
		} else {
			motor[rightWheel] = 0;
		}

		// Open seeder
		if (vexRT[Btn7D] == 1) {

			if (motor[seeder] < maxServoPos) {
				motor[seeder] = motor[seeder] + servoIncrement;
			}
		}

		// Close seeder
		if (vexRT[Btn7U] == 1) {

			if (motor[seeder] > maxServoNeg ) {
				motor[seeder] = motor[seeder] - servoIncrement;
			}
		}
		
		// Open hand
		if (vexRT[Btn8D] == 1) {

			if (motor[handLeft] < maxServoPos) {
				motor[handLeft] = motor[handLeft] + servoIncrement;
				motor[handRight] = motor[handRight] - servoIncrement;
			}
		}

		// Close Hand
		if (vexRT[Btn8U] == 1) {

			if (motor[handLeft] > maxServoNeg ) {
				motor[handLeft] = motor[handLeft] - servoIncrement;
				motor[handRight] = motor[handRight] + servoIncrement;
			}
		}

		// Button 5D raises arm
		if (vexRT[Btn5D] == 1) {
			motor[armMotor] = 100;
		} else if (vexRT[Btn6D] == 1) {
			motor[armMotor] = -100;
		} else {
			motor[armMotor] = 0;
		}

		// Button 5U rotates hand left
		if (vexRT[Btn5U] == 1) {
			motor[handMotor] = 100;
		} else if (vexRT[Btn6U] == 1) {
			motor[handMotor] = -100;
		} else {
			motor[handMotor] = 0;
		}

	}

}
