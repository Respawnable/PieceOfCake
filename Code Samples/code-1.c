int servoPos = ServoValue(servo1);
if(joy1Btn(5))          // If Button 5 is pressed:
{
      if (servoPos < 200)
      {
            servo(servo1) = servoPos++;        //raise servo until it hits position 200
      }
}
if(joy1Btn(6))          // If Button 6 is pressed:
{
      if (servoPos > 20)
      {
            servo(servo1) = servoPos--;           //lower servo until it hits position 20
       }
}

int pos = MIN_POS;

    while (true)
    {
        if (joy1Btn(6))
        {
            nxtDisplayTextLine(3, "Btn=6");
            pos += DELTA_POS;
            if (pos > MAX_POS)
            {
                pos = MAX_POS;
            }
        }
        else if (joy1Btn(8))
        {
            nxtDisplayTextLine(3, "Btn=8");
            pos -= DELTA_POS;
            if (pos < MIN_POS)
            {
                pos = MIN_POS;
            }
        }
        servo[servo1] = pos;
        servo[servo2] = pos;
        wait1Msec(10);
    }

int FORWARD = 1;
int BACKWARD = -1;
int STOPPED = 0;

int powerLevel = 0;
int powerLevelReverse = 0;
int direction = STOPPED;

float wheelDiameter = 4;
float wheelCircumference = wheelDiameter * PI;
// gearRation = (float) wheelGear / motorGear;  (2 gear example)
float gearRatio = 1.0;

void beginForward(int tempPower)
{
	direction = FORWARD;
  nSynchedMotors = synchAB;
  motor[motorL] = direction * tempPower;
}

void beginBackward(int tempPower)
{
    direction = BACKWARD;
    nSynchedMotors = synchAB;
    motor[motorL] = direction * tempPower;
}

void stopMoving()
{
    nSynchedMotors = synchNone;
    motor[motorL] = 0;
    motor[motorR] = 0;
    direction = STOPPED;
}

void untilDistance(float inches) {
  long rotationSensor = 0;
  float targetDegrees;
  rotationSensor = nMotorEncoder[motorB];
                                           // WheelCircumferenceMM is in millimeters, so, multiply inches by 25.4 to convert to mm.
  targetDegrees = 360 * inches * 25.4 / wheelCircumferenceMM * gearRatio;  // Num of Degrees to turn
  bFloatDuringInactiveMotorPWM = false;    // brake
  targetDegrees *= direction;
  targetDegrees += rotationSensor;         // Add these degrees to the current rotation sensor
  nMotorEncoderTarget[motorB] = targetDegrees; // This is the new target degree to achieve
  if(direction == STOPPED) beginDrivingForward(powerLevel);
  if(direction == (FORWARD * mDir)) {      // If going forward, then check rotation sensor <= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] <= targetDegrees) {
      if(IsFollowingLine) { FollowLinePID(); }
    }
  } else {                                 // If going backward, then check rotation sensor >= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] >= targetDegrees) {
      if(IsFollowingLine) { FollowLinePID(); }
    }
  }
}

void stopAfterDistance(float inches) { untilDistance(inches); stopMoving(); }

void untilRotations(float turnRotations) {
  long rotationSensor = 0;
  float targetDegrees;
  rotationSensor = nMotorEncoder[motorB];
                                                    // WheelCircumferenceMM is in millimeters, so, multiply inches by 25.4 to convert to mm.
  targetDegrees = 360 * turnRotations;  // Num of Degrees to turn
  bFloatDuringInactiveMotorPWM = false;             // brake
  targetDegrees *= direction;
  targetDegrees += rotationSensor;                  // Add these degrees to the current rotation sensor
  nMotorEncoderTarget[motorB] = targetDegrees;      // This is the new target degree to achieve
  if(direction == BACKWARD) {                        // If going backward, then check rotation sensor >= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] >= targetDegrees) {
      if(IsFollowingLine) { FollowLinePID(); }
    }
  } else {                                           // If going forkward, then check rotation sensor <= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] <= targetDegrees) {
      if(IsFollowingLine) { FollowLinePID(); }
    }
  }
}

void stopAfterRotations(float inches) { untilRotations(inches); stopMoving(); }

void accelerateOverDistance(float inches, int power) {
  long rotationSensor = 0;
  float targetDegrees;
  if(direction == STOPPED) beginForward(18);
  motor[motorB] = 18;              // Starting Power Level
  float powerIncrement = (power-20) / 10;
  float incrementAtDegree;
  rotationSensor = nMotorEncoder[motorB];
                                                    // WheelCircumferenceMM is in millimeters, so, multiply inches by 25.4 to convert to mm.
  targetDegrees = 360 * inches * 25.4 / wheelCircumferenceMM * gearRatio;  // Num of Degrees to turn
  bFloatDuringInactiveMotorPWM = false;             // brake
  if(direction == BACKWARD) { targetDegrees*= -1; } // Direction is reverse if <0
  targetDegrees += rotationSensor;                  // Add these degrees to the current rotation sensor
  incrementAtDegree = rotationSensor;
  nMotorEncoderTarget[motorB] = targetDegrees;      // This is the new target degree to achieve
  if(direction == FORWARD) {                        // If going forward, then check rotation sensor <= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] <= targetDegrees) {
      if(nMotorEncoder[motorB] > incrementAtDegree) {	incrementAtDegree+=36; motor[motorB] += powerIncrement; }
      if(IsFollowingLine) { FollowLinePID(); }
    }
  } else {                                           // If going backward, then check rotation sensor >= target
    while(nMotorRunState[motorB] != runStateIdle && nMotorRunState[motorB] != runStateHoldPosition && nMotorEncoder[motorB] >= targetDegrees) {
      if(nMotorEncoder[motorB] < incrementAtDegree) { incrementAtDegree-=36; motor[motorB] += powerIncrement; }
      if(IsFollowingLine) { FollowLinePID(); }
    }
  }
}

void stopAfterDistanceWithAcceleration(float inches, int power) { accelerateOverDistance(inches, power); stopMoving(); }
