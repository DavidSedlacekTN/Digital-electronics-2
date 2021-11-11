## Preparation tasks

1. Use schematic of the [Arduino Uno](../../Docs/arduino_shield.pdf) board and find out to which pins the SDA and SCL signals are connected.

   | **Signal** | **MCU pin** | **Arduino pin(s)** |
   | :-: | :-: | :-: |
   | SDA (data)  | PC4 | A4 |
   | SCL (clock) | PC5 | A5 |

2. What is the general structure of I2C address and data frames?

   | **Frame type** | **8** | **7** | **6** | **5** | **4** | **3** | **2** | **1** | **0** | **Description**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-- |
   | Address | A6 | A5 | A4 | A3 | A2 | A1 | A0 | R/W | ACK | R - Request Data[1], W - Send Data[0] |
   | Data    | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | ACK | |

3. Use the [`twi.h`](../../Examples/library/include/twi.h) header file from the I2C/TWI library to complete the description of the functions in the following table.

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `twi_init` | None | Initialize TWI, enable internal pull-up resistors, and set SCL frequency | `twi_init();` |
   | `twi_start` | Slave address | Start communication on TWI bus and send address of TWI slave | `twi_start((addr<<1)+TWI_READ);` |
   | `twi_write` | Data byte | Send one data byte to TWI slave device | `twi_write(data_byte);` |
   | `twi_read_ack` | None | Read one byte from TWI slave device and acknowledge it by ACK | `twi_read_ack();` |
   | `twi_read_nack` | None | Read one byte from TWI slave device and acknowledge it by NACK | twi_read_nack(); |
   | `twi_stop` | None | Generates stop condition on TWI bus | `twi_stop();` |