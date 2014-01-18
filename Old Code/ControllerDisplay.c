#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     ,              tmotorNone, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     ,              tmotorNone, openLoop)

#include "JoystickDriver.c"

void initializeRobot()
{

  return;
}

task main()
{
  initializeRobot();

  while (true)
  {

  	getJoystickSettings(joystick);

		nxtDisplayString(0, "joy1_x1: %d", joystick.joy1_x1);
		nxtDisplayString(1, "joy1_y1: %d", joystick.joy1_y1);
		nxtDisplayString(2, "joy1_x2: %d", joystick.joy1_x2);
		nxtDisplayString(3, "joy1_y2: %d", joystick.joy1_y2);
		nxtDisplayString(4, "Buttons: %d", joystick.joy1_Buttons);
		nxtDisplayString(5, "TopHat:  %d", joystick.joy1_TopHat);

  }
}
