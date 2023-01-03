#!/bin/bash

usage() {
    echo "Usage: $0 target board product"
    echo "Supported targets:"
    echo "  - XMC4800-2048"
    echo "Supported boards:"
    echo "  - ankle"
    echo "  - relax"
    echo "Supported products:"
    echo "  - ankle"
    echo "  - blinker"
    echo ""
    exit 1
}

arg_target=$1
arg_board=$2
arg_product=$3

CURRENT_DIR=$(pwd)

# check for help
for var in "$@"; do
    case $var in
    -h | -\? | --help)
        usage
        exit 0
        ;;
    esac
done

test -f flashBin.jlink && rm flashBin.jlink
echo "erase" >>flashBin.jlink
echo "loadfile $CURRENT_DIR/build/$arg_board/$arg_product/$arg_product.bin 0x0C000000" >>flashBin.jlink
echo "reset" >>flashBin.jlink
echo "quit" >>flashBin.jlink
./JLinkExe -device $arg_target -nogui 1 -if swd -speed 4000kHz -commandfile flashBin.jlink
