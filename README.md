# Template for EFR32 programming

See *example/* for a Makefile template and a small example program
for EFR32FG13P231F512GM48.

To create your own project, copy *example/* into your own repository
and rename it. Edit the Makefile.
If needed, add source files, include paths and defines.

Edit the `GECKOSDK` variable to point to the correct path within
a Simplicity Studio installation. It's also possible to copy the
necessary SDK files into the same repository and use a relative path.

To change the EFR32 chip, edit the Makefile below the comment
"EFR32 chip specific parts".

The Makefile can be also used for other microcontrollers by changing
SDK paths, linker script, startup code and processor core configuration.
Some parts are actually based on Makefiles generated by STM32CubeMX.
It looks a bit long and complicated, but that's partly due to the
number of comments and the clear separation of EFR32-specific parts
from rest of the commands.

For an example of a more complex project for EFR32MG1P232F256GM48, see
https://github.com/tejeez/geckokapula/tree/rail2port/firmware


# Hardware

EFR32 chips are programmed using Serial Wire Debug (SWD),
which needs at least the pins SWCLK and SWDIO.

The examples here assume a Segger J-Link is used. Other SWD adapters
may also work with a custom OpenOCD configuration file.

The hardware could be, for example, a
[Gecko Starter Kit](https://www.silabs.com/products/development-tools/wireless/mesh-networking/mighty-gecko-starter-kit)
with an integrated J-Link,
or any EFR32-based board connected to a J-Link.
[Cheap J-Link compatible adapters](https://www.ebay.com/itm/1PCS-Jlink-for-SWD-Jlink-3-Wire-for-STM32-on-SWD-Debug-NEW/152246311385)
are also known to work.


# Using command line tools on Ubuntu

Install ARM toolchain:

    sudo apt install make gcc-arm-none-eabi libnewlib-arm-none-eabi gdb-multiarch openocd

Compile the program:

    cd example
    make

To program and debug the chip, start OpenOCD:

    openocd -f board/efm32.cfg

While OpenOCD is running, start GDB:

    gdb-multiarch build/example.elf -ex "tar rem :3333"

Use these GDB commands to flash and run the program:

    load
    mon reset halt
    c


# Using Visual Studio Code

VS Code can be used as an IDE for development and debugging.

Example configuration for building and debugging using
Cortex-Debug is under *example/.vscode/*.

## Installation

The ARM toolchain is also available as a VS Code extension,
which seems to be the easiest way to install it.
It works on Windows, Linux and macOS.

Install and use the following extensions:

* **C/C++** (*Microsoft*): for C syntax highlighting and code browsing
* **Cortex-Debug** (*marus25*): to debug ARM microcontrollers
* **windows-arm-none-eabi**, **linux-arm-none-eabi** or **darwin-arm-none-eabi**
  (*metalcode-eu*): optional, to install the toolchain through VS Code

OpenOCD still needs to be installed. On Ubuntu or Debian, just do:

    sudo apt install openocd

On Windows, follow these steps:

* Download OpenOCD from https://github.com/xpack-dev-tools/openocd-xpack/releases/
* Extract the zip somewhere
* Find the path to extracted *openocd.exe*
* Open your VS Code user settings file (*settings.json*) and add: `"cortex-debug.openocdPath": "C:\\Path\To\\bin\\openocd.exe",`
* Download and run Zadig from https://zadig.akeo.ie/
* Tick *Options -> List All Devices*. Choose the *J-Link* device and *WinUSB* driver. Click *Reinstall Driver*.
* OpenOCD should now work. You can also test it on the command line by running `openocd.exe -f board/efm32.cfg`

## Use

To start programming, choose *File -> Open Folder*
and choose the `example` folder.
Press Ctrl+Shift+B to compile and F5 to start debugging.
Remember to compile the code before debugging.

To make IntelliSense work for EMLIB functions, fix the defines and paths in
*.vscode/c_cpp_properties.json* to match your EFR32 model and SDK location.


# Licensing

The Makefile template, example program and this documentation
are distributed under the MIT license.
For parts of Gecko SDK, check their respective licenses.
