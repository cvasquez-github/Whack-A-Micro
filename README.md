# Whack-A-Micro
How to use an Alesis Compact Kit 4 Electronic Drum as a USB Game Controller, using an Arduino Micro board.

![alt text](https://raw.githubusercontent.com/cvasquez-github/Whack-A-Micro/main/IMG-3058.JPG)

## Hardware
- Connect A0 to Piezo electric sensor 1 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A1 to Piezo electric sensor 2 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A2 to Piezo electric sensor 3 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect A3 to Piezo electric sensor 4 (+) pin (yellow), with a 1M Ohm resitor to ground.
- Connect GND to Piezo electric sensor 1,2,3 and 4 (-) (blue) pin.

| Arduino Micro   | Connected to                                              |
| :-------------: | :-------------:                                           |
| A0              | Drum Piezoelectric sensor 1 + (1M Ohm resitor to ground) |
| A1              | Drum Piezoelectric sensor 2 + (1M Ohm resitor to ground) |
| A2              | Drum Piezoelectric sensor 3 + (1M Ohm resitor to ground) |
| A3              | Drum Piezoelectric sensor 4 + (1M Ohm resitor to ground) |
| GND             | Drum Piezoelectric sensor 1,2,3,4 -                      |

## Arduino Software
You will need to import the Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary
When using this library, your Arduino Micro will be detected in Windows as a 32 button joystick, like this:
![alt text](https://raw.githubusercontent.com/cvasquez-github/Whack-A-Micro/main/Micro-Joystick.JPG)

Read the piezo electric sensor value using the built-in analogRead() function:
```
const int Piezo1In = A0;
float piezo1V = analogRead(Piezo1In) / 1023.0 * 5.0;
```

To push/toggle the joystick button, use the toggle the Joystick.setButton() methods, setting the button 1 on and then, a couple miliseconds later, to 0, like: 
```
if (piezo1V >= threshold && (myTime - Hit1Time) > TimeThreshold) 
    {
      Joystick.setButton(0, 1);
      delay(50);
      Joystick.setButton(0, 0);
      Hit1Time = millis();
    }
```
Take a look at the sample [PiezoToButton_Micro.ino](https://github.com/cvasquez-github/Whack-A-Micro/blob/main/PiezoToButton_Micro.ino) file.

## Unity Software
Add a fourth button to your Project Settings Input Manager:
- Name: Fire4
- Positive Button: joystick button 3

Then read your inputs inside the Update() loop and trigger the actions you want, for instance:
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

![alt text](https://github.com/cvasquez-github/Whack-A-Micro/blob/main/unity_test.gif?raw=true)
