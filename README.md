# Template for EFR32 programming

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

