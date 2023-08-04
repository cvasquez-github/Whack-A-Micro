#include <Joystick.h>
Joystick_ Joystick;

const int Piezo1In = A0;
const int Piezo2In = A1;
const int Piezo3In = A2;
const int Piezo4In = A3;

float piezo1V = 0;
float piezo2V = 0;
float piezo3V = 0;
float piezo4V = 0;

const float threshold = 0.5;

unsigned long myTime;
unsigned long Hit1Time;
unsigned long Hit2Time;
unsigned long Hit3Time;
unsigned long Hit4Time;
unsigned long TimeThreshold = 100;

void setup() {
  Joystick.begin();

  myTime = millis();
  Hit1Time = myTime;
  Hit2Time = myTime;
  Hit3Time = myTime;
  Hit4Time = myTime;
}

void loop() {

  myTime = millis();

  float piezo1V = analogRead(Piezo1In) / 1023.0 * 5.0;
  float piezo2V = analogRead(Piezo2In) / 1023.0 * 5.0;
  float piezo3V = analogRead(Piezo3In) / 1023.0 * 5.0;
  float piezo4V = analogRead(Piezo4In) / 1023.0 * 5.0;

    if (piezo1V >= threshold && (myTime - Hit1Time) > TimeThreshold) 
    {
      Joystick.setButton(0, 1);
      delay(50);
      Joystick.setButton(0, 0);
      Hit1Time = millis();
    }

    if (piezo2V >= threshold && (myTime - Hit2Time) > TimeThreshold) 
    {
       Joystick.setButton(1, 1);
      delay(50);
      Joystick.setButton(1, 0);
      Hit2Time = millis();
    }

    if (piezo3V >= threshold && (myTime - Hit3Time) > TimeThreshold) 
    {
       Joystick.setButton(2, 1);
      delay(50);
      Joystick.setButton(2, 0);
      Hit3Time = millis();
    }

    if (piezo4V >= threshold && (myTime - Hit4Time) > TimeThreshold) 
    {
       Joystick.setButton(3, 1);
      delay(50);
      Joystick.setButton(3, 0);
      Hit4Time = millis();
    }

}
