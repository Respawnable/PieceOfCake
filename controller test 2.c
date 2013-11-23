#pragma debuggerwindows ("joysticksimple");
#include "joystickdriver.c"


task main()
{
	//Integer variable that allows you to specify a "deadzone" where values (both positive or negative)
  //less than the threshold will be ignored
int threshold = 10 :

//loop forever
while(1 == 1)
{
	//Get the latest joystick values
  getJoystickSettings(joystick);
  if(abs(joystick.joy1_y2) > threshold)   // If the right analog stick's y-axis readings are either above or below the threshold...
{
    motor[rightmotor] = joystick.joy1_y2  // ...the right motor is assigned a power level equal to the right analog stick's y-axis reading.
  }
  else                                    // Else the reading are within the threshold, so
  {
  	motor[leftmotor] = 0;                 // ...the right motor is stopped with a power level of 0.
  }
}




}
