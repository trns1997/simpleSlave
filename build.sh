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
ARM_TOOLCHAIN_FILE=$CURRENT_DIR/board/arm-none-eabi-gcc.cmake

# check for help
for var in "$@"; do
    case $var in
    -h | -\? | --help)
        usage
        exit 0
        ;;
    esac
done

case $arg_target in
XMC4800-2048)
    export TARGET_DEVICE="XMC4800-2048"
    ;;
*)
    echo "!!! Unknown target '$arg_target' !!!"
    usage
    exit 1
    ;;
esac

rm -rf $CURRENT_DIR/build/$arg_board/$arg_product
mkdir -p $CURRENT_DIR/build/$arg_board/$arg_product
cd $CURRENT_DIR/build/$arg_board/$arg_product
cmake -G "Unix Makefiles" -DARM_TOOLCHAIN_DIR=${ARM_GCC_BIN_FOLDER} -DCMAKE_TOOLCHAIN_FILE=$ARM_TOOLCHAIN_FILE -DTOP_BIN_DIR:STRING=$CURRENT_DIR/build/$arg_board -DBOARD_NAME:STRING=$arg_board -DPRODUCT_NAME:STRING=$arg_product -DMCU_NAME:STRING=XMC4800_F144x2048 $CURRENT_DIR
make -j8