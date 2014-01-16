#pragma config(Sensor, S2, HTIRS2, sensorI2CCustom)
//#pragma config(Sensor, S1 ,     IRSeeker,       sensorHiTechnicIRSeeker1200)
//
// IRSeek.c - a simple program to demonstrate how to use the
// HiTechnic IR Seeker V2 sensor. This program requires
// the HTIRS2-driver.h driver provided with RobotC.
//
// You can copy the "drivers" subdirectory and place it
// in the same directory as this source file. if you do,
// you can use the following #include statement to specify
// the path to the driver.
//#include "drivers/HTIRS2-driver.h"
// if you use the "drivers/HTIRS2-driver.h" line,
// then you should comment out the following line.
#include ".\rdpartyrobotcdr-3.3.1\drivers\hitechnic-irseeker-v2.h"
// sTextLines is an array of strings - used to keep
// track of if changes to display occur.
string sTextLines[8];
// function prototype
void displayText(int nLineNumber, string cChar, int nValueDC, int nValueAC);

// main task
task main ()
{
	// dc and ac directional values.
	int _dirDC = 0;
	int _dirAC = 0;
	// DC and AC values from 5 internal detectors.
	int dcS1, dcS2, dcS3, dcS4, dcS5 = 0;
	int acS1, acS2, acS3, acS4, acS5 = 0;
	// we are going to set DSP mode to 1200 Hz.
	tHTIRS2DSPMode _mode = DSP_1200;
	// attempt to set to DSP mode.
	if (HTIRS2setDSPMode(HTIRS2, _mode) == 0)
	{
		// unsuccessful at setting the mode.
		// display error message.
		eraseDisplay();
		nxtDisplayCenteredTextLine(0, "ERROR!");
		nxtDisplayCenteredTextLine(2, "Init failed!");
		nxtDisplayCenteredTextLine(3, "Connect sensor");
		nxtDisplayCenteredTextLine(4, "to Port 2.");
		// make a noise to get their attention.
PlaySound(soundDownwardTones);
		// wait so user can read message, then leave main task.
		wait10Msec(300);
		return;
	}
	// initialize the array sTextLines.
	for (int i = 0; i < 8; ++i)
		sTextLines[i] = "";
	// display some header info at top of screen
	eraseDisplay();
	nxtDisplayTextLine(0, "  Piece Of Cake  ");
	nxtDisplayTextLine(1, "------3763-------");
	// loop continuously and read from the sensor.
	while(true)
	{
		// Read the current non modulated signal direction
	//_dirDC = HTIRS2readDCDir(HTIRS2);
	//	if (_dirDC < 0)
			//break; // I2C read error occurred
		//// read the current modulated signal direction
		_dirAC = HTIRS2readACDir(HTIRS2);
		if (_dirAC < 0)
			break; // I2C read error occurred
		//// Read the individual signal strengths of the internal sensors
		//// Do this for both unmodulated (DC) and modulated signals (AC)
		//if (!HTIRS2readAllDCStrength(HTIRS2, dcS1, dcS2, dcS3, dcS4, dcS5))
		//	break; // I2C read error occurred
		if (!HTIRS2readAllACStrength(HTIRS2, acS1, acS2, acS3, acS4, acS5 ))
			break; // I2C read error occurred
		nxtDisplayTextLine(2, "Position %d", _dirAC);
		nxtDisplayTextLine(3, "Strength0 %d", acS1);
		nxtDisplayTextLine(4, "Strength1 %d", acS2);
		nxtDisplayTextLine(5, "Strength2 %d", acS3);
		nxtDisplayTextLine(6, "Strength3 %d", acS4);
		nxtDisplayTextLine(7, "Strength4 %d", acS5);
		// wait a little before resuming.
		wait10Msec(5);
	}
}
// Minimize LCD screen flicker by only updating LCD when data has changed
void displayText(int nLineNumber, string cChar, int nValueDC, int nValueAC)
{
	string sTemp;
	StringFormat(sTemp, "%4d %4d", nValueDC, nValueAC);
	// Check if the new line is the same as the previous one
	// Only update screen if it's different.
	if (sTemp != sTextLines[nLineNumber])
	{
		string sTemp2;
		sTextLines[nLineNumber] = sTemp;
		StringFormat(sTemp2, "%s: %s", cChar, sTemp);
		nxtDisplayTextLine(nLineNumber, sTemp2);
	}
}
