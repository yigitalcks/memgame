Task 01: The RIOT Shell
=======================

Getting to Know Your Board
--------------------------

The board you will be working in this software project is the nRF52840 DK.
Make yourself familiar with the basic features of the board using the [Data Brief](https://www.nordicsemi.com/-/media/Software-and-other-downloads/Product-Briefs/nRF52840-DK-product-brief.pdf) and the [User Guide](https://infocenter.nordicsemi.com/pdf/nRF52840_DK_User_Guide_20201203.pdf).
You should be able to answer the following questions:

1. Does the board contain an integrated programmer?
1. Does the board contain an integrated debugger?
1. Does the board contain an integrated UART to USB bridge?
1. What processor is used on the board?
    - What architecture has it ( e.g. RISC-V, x86, MIPS, ...)?
    - What instruction set level is supported (e.g. ARMv6-M, ARMv8.1-M, RV32IMAC, ...)
    - What is the maximum core clock?
    - How much RAM and ROM is available?
1. Does the board has an integrated network device?
    - Is it wired or wireless?
    - Which standards (e.g. IEEE 802.3, IEEE 802.11, IEEE 802.15.4, BLE, ...) does it support?
1. Are there any buttons on the board?
    - Are any of them available as inputs to the program running on the board?
    - Are there any special buttons e.g. to reset the board?
1. Are there any LEDs on the board?
    - Are any of them available for control via the program running on the boards?
    - Are there any status LEDs indicating hardware states, power states, etc?
1. What connectors are available?
    - Do they comply with popular standards, e.g. USB, Arduino Shields, Grove Connectors, ...
1. What serial interfaces are supported?
    - E.g. USB, SPI, I2C, ...

Flash this Program
------------------

You can compile, flash and connect to the board using `make`.
The target `all` (default) will compile the program.
The target `flash` will flash the program and depends on `all` - so just running `make flash` will recompile and flash.
The target `term` will connect to the board using the default serial interface, which is via UART in case of your board.
Summing up, all of the above can be achieved using:

```
make flash term
```

Getting to Know the Shell
-------------------------

1. Get a list of supported RIOT shell commands
1. Reboot the board
1. Figure out what the current version of RIOT is that is running on the board
1. Get a list of sensors and actuators on the board
1. Read out the current room temperature
1. Turn on all LEDs
1. Which threads are currently running on the board?
1. How much free stack space has the main thread?
1. Does the number of free stack space vary?
    - E.g. what is it directly after rebooting the board, what is it after reading the temperature.
    - Note: RIOT only measures the *worst case* stack consumption, not the *current* stack consumption.
    - Why is the worst case stack consumption more interesting?
