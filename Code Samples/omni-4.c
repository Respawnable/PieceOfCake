#include "API.h"

void main ( void )
{
int LF; // Left Front
int RF; // Right Front
int LR; // Left Rear
int RR; // Right Rear
int leftx;
int lefty;
int rightx;
int spin;
      while ( 1 )
      {
            // Get Data 
            leftx = GetRxInput ( 1 , 4 ) ; // Left Joystick, X Axis
            lefty = GetRxInput ( 1 , 3 ) ; // Left Joystick, Y Axis
            rightx = GetRxInput ( 1 , 1 ) ; // Right Joystick, X Axis
            // Half the input signal (so code does not overflow past 255)
            leftx = leftx / 2 ;
            lefty = lefty / 2 ;
            spin = rightx / 2 ;
            // Drive Code Algorithim
            LF = RR = lefty - leftx + 127 ;
            RF = LR = 255 - lefty - leftx ;
            RR = 255 - RR ; // Reverse Direction of RR motor
            LR = 255 - LR ; // Reverse Direction of LR motor
            // Spin Code Algorithim
            RF = RF - spin + 63 ;
            RR = RR - spin + 63 ;
            LF = LF - spin + 63 ;
            LR = LR - spin + 63 ;
            // Code overflow prevention
            if ( LF < 0 )
            {
                  LF = 0 ;
            }
            else if ( LF > 255 )
            {
                  LF = 255 ;
            }
            if ( RF < 0 )
            {
                  RF = 0 ;
            }
            else if ( RF > 255 )
            {
                  RF = 255 ;
            }
            if ( RR < 0 )
            {
                  RR = 0 ;
            }
            else if ( RR > 255 )
            {
                  RR = 255 ;
            }
            if ( LR < 0 )
            {
                  LR = 0 ;
            }
            else if ( LR > 255 )
            {
                  LR = 255 ;
            }
            // Set Motors
            SetMotor ( 1 , RF ) ;
            SetMotor ( 2 , LF ) ;
            SetMotor ( 3 , LR ) ;
            SetMotor ( 4 , RR ) ;
      }
}

#define MAXMOTORSPEED 50

const float sqrt3div2 = 0.866025;

int round(float f)
{
  return (f>0)?(int)(f+0.5):(int)(f - 0.5);
}

void getMotorSpeeds(int &motorSpeedA, int &motorSpeedB, int &motorSpeedC, int angle, int Vb) {
  float Vw1, Vw2, Vw3, norm_factor;

  Vw1 = Vb*cosDegrees(angle);
  Vw2 = Vb*(-0.5*cosDegrees(angle) + sqrt3div2*sinDegrees(angle));
  Vw3 = Vb*(-0.5*cosDegrees(angle) - sqrt3div2*sinDegrees(angle));

  norm_factor = 1.0;

  if (Vw1 > MAXMOTORSPEED) {
    norm_factor = MAXMOTORSPEED / Vw1;
  } else if (Vw2 > MAXMOTORSPEED) {
    norm_factor = MAXMOTORSPEED / Vw2;
  } else if (Vw3 > MAXMOTORSPEED) {
    norm_factor = MAXMOTORSPEED / Vw3;
  }

  motorSpeedA = round(Vw1 * norm_factor);
  motorSpeedB = round(Vw2 * norm_factor);
  motorSpeedC = round(Vw3 * norm_factor);
}

