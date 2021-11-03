## Preparation Tasks

1. Find out the connection of five push buttons: Select, Left, Up, Down, and Right.

   | **Button** | **Switch** | **Connects to** | **Connects via** |
   | :-: | :-: | :-: | :-: |
   | RIGHT | SW1 | PC0 | Voltage divider 3k/5,25k |
   | UP | SW2 | PC0 | Voltage divider 3,33k/4,92k |
   | DOWN | SW3 | PC0 | Voltage divider 3,92k/4,3k |
   | LEFT | SW4 | PC0 | Voltage divider 3,92k/4,3k |
   | SELECT | SW5 | PC0 | Voltage divider 4,92k/3,3k |
   | RST | SW6 | RESET | No Resistor |

2. According to the connection, calculate the voltage values on pin PC0[A0] if one button is pressed at a time. In this case, the voltage on the pin is given by the [voltage divider](https://www.allaboutcircuits.com/tools/voltage-divider-calculator/), where resistors R3, R4, R5 and R6 are applied successively.

   ![Equation: Voltage divider](Images/Voltage_Divider_1.png)

   ![Equation: Voltage divider](Images/Voltage_Divider_2.png)

   ![Equation: Voltage divider](Images/Voltage_Divider_3.png)

3. Calculate the voltage value if none of the push buttons is pressed.

   ![Equation: Voltage divider](Images/Voltage_Divider_4.png)

4. Calculate the ADC values for these voltages according to the following equation if reference is Vref=5V and number of bits for analog to digital conversion is n=10.

   ![Equation: ADC conversion](Images/ADC_Example.png)

   | **Push button** | **PC0[A0] voltage** | **ADC value (calculated)** | **ADC value (measured)** |
   | :-: | :-: | :-: | :-: |
   | Right  | 0V | 0   |  |
   | Up     | 0.495V | 101 |  |
   | Down   | 1.203V | 246 |  |
   | Left   | 1.970V | 403 |  |
   | Select | 3.182V | 651 |  |
   | None   | 5.0V | 1023 |  |



