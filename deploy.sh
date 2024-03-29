#!/bin/bash

usage() {
    echo "Usage: $0 target product board"
    echo "Supported targets:"
    echo "  - XMC4800-2048"
    echo "Supported products:"
    for dir in product/*/; do
        product=$(basename "$dir")
        echo "  - $product"
    done
    echo "Supported boards:"
    for dir in product/$product/board/*/; do
        board=$(basename "$dir")
        echo "  - $board"
    done
    echo ""
    exit 1
}

arg_target=$1
arg_product=$2
arg_board=$3

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

if [ ! -f "$CURRENT_DIR/build/$arg_board/$arg_product/$arg_product.bin" ]; then
    echo "BIN FILE DOES NOT EXIST HAVE YOU TRIED BUILDING FIRST"
    exit 0
fi

test -f flashBin.jlink && rm flashBin.jlink
#TODO in the future for prod deployment: echo "erase" >>flashBin.jlink
echo "loadfile $CURRENT_DIR/build/$arg_board/$arg_product/$arg_product.bin 0x0C000000" >>flashBin.jlink
echo "reset" >>flashBin.jlink
echo "quit" >>flashBin.jlink
./JLinkExe -device $arg_target -nogui 1 -if swd -speed 4000kHz -commandfile flashBin.jlink
