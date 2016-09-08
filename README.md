# Elektor AVR Board Package for Arduino IDE
This repository contains the package descriptor for Elektor's Arduino compatible boards.

Supports:
- Platino (16 MHz)
- eRIC Nitro (8 MHz)
- AVR Playground (8 MHz)
- eRIC Nitro R4 (8 MHz with ATmega328PB)
- Elektor Uno R4 (like Arduino Uno R3 but with ATmega328PB, 8 MHz & 16 MHz)

URLs for the IDE:
- All boards, but Windows-only for the Elektor Uno R4:
  https://raw.githubusercontent.com/ElektorLabs/arduino/master/package_elektor_boards_index.json
- Elektor Uno R4 only (Windows/Linux/Mac), Arduino IDE 1.6.7 & 1.6.9 (do not use 1.6.8): 
  https://raw.githubusercontent.com/ElektorLabs/arduino/master/package_elektor_uno_r4_index.json
- Elektor Uno R4 only (Windows/Linux/Mac), Arduino IDE 1.6.1x: 
  https://raw.githubusercontent.com/ElektorLabs/arduino/master/package_elektor_uno_r4_1_6_10_index.json
 
Use the Arduino IDE Boards Manager to install this package, as follows:
- Open the Arduino IDE's Preferences dialog: File -> Preferences
- Add one (or all, separate multiple URLs with commas) of the URLs above to the edit box 
  "Additional Boards Manager URLs" (Arduino IDE 1.6.6 or higher).
- Open the IDE's Boards Manager: Tools -> Board -> Boards Manager
- As Type (upper left corner) select Contributed. You should now see at least one entry for Elektor boards.
- Click on the entry that you want to install to make the install button appear.
- Click the Install button to install the boards. Close the dialog when done.

Open the available boards list (Tools -> Board) and scroll down to the a header "Elektor Labs" followed by
the Elektor boards. Choose the one you need.

After selecting Platino you must also choose the processor: Tools -> Processor

Platino comes with its own core that contains drivers for the on-board peripherals like the rotary encoder,
the pushbuttons, the LED and/or RGB LED, the buzzer and the LCD. This core consumes memory. If you want to use 
Platino without the drivers select "Platino without library" from the boards list.

Bootloaders for all supported boards and processors are provided in the package. You can burn them with the 
Arduino as ISP sketch (or any other supported ISP programmer for that matter).

Everything has been tested with Arduino IDE 1.6.7 and 1.6.11.

Do not use Arduino IDE 1.6.8 because it has a serious serial port problem.

Since 1.6.10 & 1.6.11 we occasionally run into a strange linker error "ld returned 5 exit status". This is a 
known long-standing but unresolved issue unrelated to your code but to something unknown. Switch to 1.6.7 if you 
run into this problem.

P.S. Previous JSON files with a version number in their name have been replaced by "package_elektor_boards_index.json"