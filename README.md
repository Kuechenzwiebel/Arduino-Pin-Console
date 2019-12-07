# Arduino-Pin-Console
This is a tool that allows you to control your Arduino pins with your serial-console.

# Features and usage
At the start of the program it will ask you which pin should be a input or output. 
An input for a specific pin can be set by sending `in` or `IN`. For an output `out` or `OUT` needs to be sent. 

If you set the variable `usePresetPinStates` to `true`, the program won't ask you for the pin states
and instead use the modes set in the array `pinStates`. In the array, `1` means output and `0` means input.


**After your arduino will send you `Configuration done!`, you can start controlling your pins**

Sending `high` or `HIGH` will ask you to input a pin number that should be put on high. 
Writing `low` or `LOW` will set that pin to low.

Typing in `read` or `READ` will ask you for a pin number and then will return the current state of this pin.

`analogread` or `ANALOGREAD` will send you the state of an analog pin in units between `0` and `1023` like arduino uses 
but also will return the voltage at this pin.

Writing `pulse` or `PULSE` will ask you for a pin and a pulse width in milliseconds. 
Now a single pulse with the specified pulsewidth will be put out on the pin.

`rpulse` or `RPULSE` also will ask you for the number of pulses that should be put out. The duty cycle is 50%.

Using `pinmodes` or `PINMODES` will put out your pinstates. This is directly formated to put it into the `pinStates` array.

`pinstates` or `PINSTATES` will put out the current state of every pin.

# Installation
You need to install the `ArduinoSTL` library first. 
Depending on your IDE, you might have to copy the content of the `main.cpp` file into your main file.
The `MIN_PIN` and `MAX_PIN` defines in the code may have to be adjusted depending on what arduino you are using. 
The default is for an Arduino Uno.
