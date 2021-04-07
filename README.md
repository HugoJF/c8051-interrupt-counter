# C8051 interrupt counts 

Firmware that counts how many interrupts are triggered in /INT0 and prints them using UART to serial terminal.

This firware reads '1' from serial terminal to trigger a virtual switch that emulates a real switch with bounces. This virtual switch triggers /INT0 by a wire connecting P1_2 to P1_0 (configured for /INT0).

SPI0 and SMBus ports are enabled in order to push /INT0 to port 1.

Timer 0 is used for serial communication, while Timer 3 is used as a 5ms timer to help drive the virtual switch behavior (bouncing 2 times per press).

Code is missing lots of comments because most part was taken from other examples.
