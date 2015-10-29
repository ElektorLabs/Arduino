# Elektor AVR Board Package for Arduino IDE
This repository contains the package descriptor for Elektor's Arduino compatible boards.

Supports:
- Platino (16 MHz)
- eRIC Nitro (8 MHz)

Use the Arduino IDE Boards Manager to install this package, as follows:

- Open the Arduino IDE's Preferences dialog: File -> Preferences
- Arduino IDE 1.6.6: https://raw.githubusercontent.com/ElektorLabs/arduino/master/package_elektor-labs.com_ide-1.6.6_index.json 
  Arduino IDE 1.6.5: https://raw.githubusercontent.com/ElektorLabs/arduino/master/package_elektor-labs.com_ide-1.6.5_index.json 
  Add the one of the two URLs to the edit box "Additional Boards Manager URLs". It is possible to have multiple URLs as long as 
  you separate them with commas.
- Open the IDE's Boards Manager: Tools -> Board -> Boards Manager
- As Type (upper left corner) select Contributed. You should now see an entry for Elektor AVR Boards.
- Click the Install button to install the boards. Close the dialog when done.

Now when you open the available boards list (Tools -> Board) there will be a header "Elektor Labs" followed by
the Elektor boards. Choose the one you need.

After selecting Platino you must also choose the processor: Tools -> Processor

Platino comes with its own core that contains drivers for the on-board peripherals like the rotary encoder,
the pushbuttons, the LED and/or RGB LED, the buzzer and the LCD. This core consumes memory. If you want to use 
Platino without the drivers select "Platino without library" from the boards list.

Bootloaders for all supported boards and processors are provided in the package. You can burn them with the 
Arduino as ISP sketch (or any other supported ISP programmer for that matter).

Everything has been tested with Arduino IDE 1.6.5 and 1.6.6.
