# Lab 4: Interrupts, timers

1. Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128 and other timers have only 5 prescaler values.

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16u | 128u | -- | 1.024m | -- | 4.096m | 16.384m |
| Timer/Counter1 | 16 | 4.096m | 32.768m | -- | 262.144m | -- | 1.048576 | 4.194304 |
| Timer/Counter2 | 8  | 16u | 128u | 512u | 1.024m | 2.048m | 4.096m | 16.384m |

2. Shields are boards that can be attached to an Arduino board, significantly expand its capabilities, and makes prototyping much faster. See schematic of [Multi-function shield](../../Docs/arduino_shield.pdf) and find out the connection of four LEDs (D1, D2, D3, D4) and three push buttons (S1-A1, S2-A2, S3-A3).

| **LED** | **Connects to** | **Connects via** |
| :-: | :-: | :-: |
| D1 | PB5 | 1k Ohm resistor |
| D2 | PB4 | 1k Ohm resistor |
| D3 | PB3 | 1k Ohm resistor |
| D4 | PB2 | 1k Ohm resistor |

| **Button** | **Connects to** | **Pull-up resistor value** |
| :-: | :-: | :-: |
| S1-A1 | PC1 | 10k Ohm resistor |
| S1-A2 | PC2 | 10k Ohm resistor |
| S3-A3 | PC3 | 10k Ohm resistor |