// This script reads 4 Piezo Electric Sensors and triggers Joystick Buttons accordingly.
// Works on Arduino Micro Pro boards
// By Carlos Vasquez <https://github.com/cvasquez-github/>

#include <Joystick.h>
Joystick_ Joystick;

const float PiezoValueThreshold = 0.8;
const unsigned long TimeThreshold = 100;
const unsigned long TimeButtonRelease = 50;

float piezo1V = 0;
float piezo2V = 0;
float piezo3V = 0;
float piezo4V = 0;

unsigned long currentTime;
unsigned long HitTime;
int Hit = 0;

void setup() {
  Joystick.begin(true);
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(0, 255);
  ResetAxes();
  currentTime = millis();
  HitTime = currentTime;
}

void ResetAxes()
{
  Joystick.setXAxis(0);
  Joystick.setYAxis(0);
  Joystick.setZAxis(0);
}

int GetIndexFromValue(float value)
{
if (value == piezo1V) { return 1; }
else if (value == piezo2V) { return 2; }
else if (value == piezo3V) { return 3; }
else if (value == piezo4V) { return 4; }
else { return 0; }
}

float GetMaxValue()
{
return max(max(max(piezo1V, piezo2V), piezo3V), piezo4V);
}

int maxIndex = 0;

void loop() {

  // Get current time in millis.
  currentTime = millis();

  // Read all 4 analog inputs.
  piezo1V = (analogRead(A3) / 1023.0 * 5.0);
  piezo2V = (analogRead(A2) / 1023.0 * 5.0);
  piezo3V = (analogRead(A1) / 1023.0 * 5.0);
  piezo4V = (analogRead(A0) / 1023.0 * 5.0);

  // Get the Piezo that has been hit harder (this is to avoid secondary piezos readings caused only by vibration when hitting a close one)
  maxIndex = GetIndexFromValue(GetMaxValue());

  if (Hit == 0 && maxIndex == 1 && piezo1V >= PiezoValueThreshold && (currentTime - HitTime) > TimeThreshold) 
  {
    // If Piezo 1 is hit, Press Button 1
    Hit = 1;
    HitTime = millis();
    Joystick.setButton(0, 1);
  }
  else if (Hit == 1 && ((currentTime - HitTime) > TimeButtonRelease))
  {
    // If Piezo 1 was hit and timeout is reached, Release Button 1
    Joystick.setButton(0, 0);
    Hit = 0;
  }
    
  if (Hit == 0 && maxIndex == 2 && piezo2V >= PiezoValueThreshold && (currentTime - HitTime) > TimeThreshold) 
    {
    // If Piezo 2 is hit, Press Button 2
    Hit = 2;
    HitTime = millis();
    Joystick.setButton(1, 1);
    }
  else if (Hit == 2 && ((currentTime - HitTime) > TimeButtonRelease))
    {
      // If Piezo 2 was hit and timeout is reached, Release Button 2
      Joystick.setButton(1, 0);
      Hit = 0;
    }

    
    if (Hit == 0 && maxIndex == 3 && piezo3V >= PiezoValueThreshold && (currentTime - HitTime) > TimeThreshold) 
    {
      // If Piezo 3 is hit, Press Button 3
       Hit = 3;
       HitTime = millis();
       Joystick.setButton(2, 1);
    }
    else if (Hit == 3 &&  ((currentTime - HitTime) > TimeButtonRelease))
    {
      // If Piezo 3 was hit and timeout is reached, Release Button 3
      Joystick.setButton(2, 0);
      Hit = 0;
    }
    
    if (Hit == 0 && maxIndex == 4 && piezo4V >= PiezoValueThreshold && (currentTime - HitTime) > TimeThreshold) 
    {
      // If Piezo 4 is hit, Press Button 4
       Hit = 4;
       HitTime = millis();
       Joystick.setButton(3, 1);
    }
    else if (Hit == 4 &&  ((currentTime - HitTime) > TimeButtonRelease))
    {
      // If Piezo 4 was hit and timeout is reached, Release Button 4
      Joystick.setButton(3, 0);
      Hit = 0;
    }
}
