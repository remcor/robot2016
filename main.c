#pragma config(Motor, port2, seeder, tmotorServoStandard, openLoop)
#pragma config(Motor, port3, leftWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port4, rightWheel, tmotorVex393_MC29, openLoop)
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
	// Define the min and max a servo can rotate
	int maxServoPos = 127;
	int maxServoNeg = -127;
	
	// Amount to increment servo rotation
	int servoIncrement = 10;

	// Joystick threshold
	int threshold = 10;

	// Main loop
	while (true) {

		/*
			To prevent the left and right wheel motors from humming we set a threshold.
			The joysticks are never true 0.
			So we make sure the joystick has moved more then a threshold.
			This ensures it was intentional.
		*/
    
		// If left joystick is moved greater then threshold.
		if (vexRT[Ch3] > threshold || vexRT[Ch3] < -threshold) {
			// Left Joystick Y value
			motor[leftWheel] = vexRT[Ch3]; 
		} else {
			// Joystick isnt moving so make sure motor isn't moving.
			motor[leftWheel] = 0; 
		}

		// If right joystick is moved greater then threshold.
		if (vexRT[Ch2] > threshold || vexRT[Ch2] < -threshold) {
			// Right Joystick Y value
			motor[rightWheel] = vexRT[Ch2]; 
		} else {
			// Joystick isnt moving so make sure motor isnt moving.
			motor[rightWheel] = 0; 
		}

		// Check if Button 7D is pressed to open seeder.
		if (vexRT[Btn7D] == 1) {
			// Make sure the servo isnt at the max position already.
			if (motor[seeder] < maxServoPos) {
				// Take current servo postition and increment by servo Increment
				motor[seeder] = motor[seeder] + servoIncrement; 
			}
		}

		// Check if Button 7U is pressed to close seeder.
		if (vexRT[Btn7U] == 1) {
  			// Make sure the servo isnt at the min position already.
			if (motor[seeder] > maxServoNeg ) {
				// Take current servo postition and decrease by servo Increment
				motor[seeder] = motor[seeder] - servoIncrement; 
			}
		}
		
			// Check if Button 8D is pressed to open hand.
		if (vexRT[Btn8D] == 1) {
			// Make sure the servo isnt at the max position already. 
			if (motor[handLeft] < maxServoPos) {
				// Increment left side of hand
				motor[handLeft] = motor[handLeft] + servoIncrement; 
				// Decrease right side of hand
				motor[handRight] = motor[handRight] - servoIncrement; 
			}
		}

		// Check if Button 8U is pressed to close hand.
		if (vexRT[Btn8U] == 1) {
  			// Make sure the servo isnt at the min position already.
			if (motor[handLeft] > maxServoNeg ) {
				// Decrease left side of hand
				motor[handLeft] = motor[handLeft] - servoIncrement; 
				// Increase right side of hand
				motor[handRight] = motor[handRight] + servoIncrement; 
			}
		}

		// Check if Button 5D is pressed to raise arm.
		if (vexRT[Btn5D] == 1) {
			// Rotate motor to raise arm
			motor[armMotor] = 100; 
			
		// Check if Button 6D is pressed to lower arm.
		} else if (vexRT[Btn6D] == 1) {
			// Provide a negative value which rotates the motor the opposite direction and lowers the arm.
			motor[armMotor] = -100; 
		} else {
			// Stop motor
			motor[armMotor] = 0; 
		}

		// Check if Button 5U is pressed to rotate hand left
		if (vexRT[Btn5U] == 1) {
			// Rotate motor to rotate hand
			motor[handMotor] = 100; 
			
		// Check if Button 6U is pressed to rotate hand right
		} else if (vexRT[Btn6U] == 1) {
			// Provide a negative value which rotates the motor the opposite direction and rotates the hand right
			motor[handMotor] = -100; 
		} else {
			// Stop motor
			motor[handMotor] = 0; 
		}
	}
}
