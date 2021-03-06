# EEPROM-Programmer
GPIO and EEPROM programming API designed for the BeagleBone Black. 
EEPROM-Prog program uses both interfaces to program data into an EEPROM.

The GPIO programming interface allows for the use of GPIO pins available on the BeagleBone Black to be used in general programs. It allows for
the changing of GPIO characterstics in your code without having to manipulate the state of the GPIO pins through the terminal by opening, writing, and
closing device files.

The Prog programming interface uses the GPIO interface and allows for the integration of an EEPROM programmer that uses a serial input
and parallel load hardware interface using shift registers. This then allows the writing of a certain value to a given address
by parallel loading the address and data values onto the EEPROM and then issuing a write command to the hardware to load the value at the given address.

The GPIO and Prog programming interfaces can be used to work with any EEPROM by treating n-bit-address, n-bit-data, and write-enable as abstract registers that can be
written to. These abstract regists then require a clock, clear, and data pins which translate directley to the serial-shift hardware that we would be using to program the EEPROMs.

The hardware that I used is a AT28C16 (http://cva.stanford.edu/classes/cs99s/datasheets/at28c16.pdf) as well as a serial-shift parallel-loading
hardware framework to load 8-bit data at a given 11-bit address. 
Album with pictures of hardware used: https://imgur.com/a/81xC4c5
The EEPROM-Prog program uses the BBB GPIO Device framework and uses 7 pins in total.
  - 3 GPIO pins for the Data register's clear(grey), clock(white), and data(blue) pins.
  - 3 GPIO pins for the Address registers's clear(grey), clock(white), and data(blue) pins.
  - 1 GPIO pin for the Write(yellow) pin which loads the Data at the address seen by the EEPROM.

If one wishes to accomodate the main.cpp program that I have written for their own uses, the pins that are to be used can be 
changed in the main.cpp when constructing the Prog objects. A data Prog object and an address Prog object, GPIO write pin must 
also be specified. If there are not enough available GPIO pins on the BBB, a tutorial on how to free up more pins is included 
below in the README.


# COMPILING and RUNNING
[WARNING] YOU MUST RUN THIS PROGRAM WITH ELEVATED PRIVILEGES

Typing 'make' will compile the program into an executable called "EEPROM-Prog"

An example is as follows:

    $ make

A datafile must be passed as an arguement that has the address values and the data values that are to be programmed.
An example of one of these files can be found in the Example_Files directory.

running with the executable compiled:

    $ sudo ./EEPROM-Prog [datafile.txt]

# FREEING UP GPIO PINS THROUGH THE DEVICE-OVERLAYS
- For 3.X Linux Kernel images for BBB
      ***CAUTION YOUR BBB MIGHT NOT BOOT IF YOU DISABLE THE WRONG THINGS***
      
Available GPIO pins must be used for the program. If there are not enough you must free them up through the disabling
of device-overlays that dictate what hardware gets assigned to what task on the BBB. 
To do this first access the file uEnv.txt. It is located in /boot/ directory. 
In this file you will see a line like this:

##BeagleBone Black: HDMI (Audio/Video) disabled:
##10 dtb=am335x-boneblack-emmc-overlay.dtb

Uncomment the second line here. Make sure that only this line is uncommented.
Uncommenting this device-overlay will free up pins used by the HDMI. If you uncomment this line you will not be able to use
HDMI capabilities.

If you uncomment the device-overlay that disables the onboard eMMC memory, you device will not boot and will have to be boot
from an SSD or reinstall your image. Be careful and be sure you know what you're doing.

# CONTACT
Any question or comments can be directed to lnowakow@eng.ucsd.edu
