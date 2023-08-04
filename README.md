# Whack-A-Micro
How to convert an Alesis Compact Kit 4 Electronic Drump into a USB Game Controller, using an Arduino Micro board.

![alt text](https://raw.githubusercontent.com/cvasquez-github/Whack-A-Micro/main/IMG-3058.JPG)

## Hardware
- Connect A0 to Piezo electric sensor 1 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A1 to Piezo electric sensor 2 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A2 to Piezo electric sensor 3 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A3 to Piezo electric sensor 4 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect GND to Piezo electric sensor 1,2,3 and 4 (-) (blue) pin.

| Arduino Micro   | Connected to                                              |
| :-------------: | :-------------:                                           |
| A0              | Drump Piezoelectric sensor 1 + (1M Ohm resitor to ground) |
| A1              | Drump Piezoelectric sensor 2 + (1M Ohm resitor to ground) |
| A2              | Drump Piezoelectric sensor 3 + (1M Ohm resitor to ground) |
| A3              | Drump Piezoelectric sensor 4 + (1M Ohm resitor to ground) |
| GND             | Drump Piezoelectric sensor 1,2,3,4 -                      |

## Arduino Software
You will need to import the Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary

Then read each analog input like:
```
const int Piezo1In = A0;
float piezo1V = analogRead(Piezo1In) / 1023.0 * 5.0;
```

Finally, toggle the corresponding Button ON and then OFF back again like:
```
if (piezo1V >= threshold && (myTime - Hit1Time) > TimeThreshold) 
    {
      Joystick.setButton(0, 1);
      delay(50);
      Joystick.setButton(0, 0);
      Hit1Time = millis();
    }
```
Take a look at the sample [PiezoToButton_Micro.i](https://github.com/cvasquez-github/Whack-A-Micro/blob/main/PiezoToButton_Micro.ino) file.

## Unity Software
Add a third button to your Project Settings Input Manager:
- Name: Fire4
- Positive Button: joystick button 3

Then read your inputs inside the Update() loop and fire the actions you want like:
```
if (Input.GetButtonDown("Fire1"))
        {
            // Spawn Button 1 effect
            Instantiate(OneEffect, new Vector3(0, 0, 0), Quaternion.identity);

            // Hides an object (for instance to display the one underneath)
            OneOff.SetActive(false);

            // Starts a couroutine to show the hidden object back again after a couple miliseconds.
            StartCoroutine(ShowTimeout(OneOff, 0.05f));
        }
```
