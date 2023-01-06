#!/bin/bash

usage() {
    echo "Usage: $0 mcu product board"
    echo "OR"
    echo "Usage: $0 unit"
    echo "Supported mcus:"
    echo "  - XMC4800_F144x2048"
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

arg_mcu=$1
arg_product=$2
arg_board=$3

cmake_args=""
cmake_toolchain_dir="-DARM_TOOLCHAIN_DIR="
cmake_toolchain_file="-DCMAKE_TOOLCHAIN_FILE="
cmake_top_bin_dir="-DTOP_BIN_DIR:STRING="
cmake_board_name="-DBOARD_NAME:STRING="
cmake_product_name="-DPRODUCT_NAME:STRING="
cmake_mcu_name="-DMCU_NAME:STRING="
cmake_build_type="-DCMAKE_BUILD_TYPE="
cmake_test_bool="-DTEST:BOOL="

CURRENT_DIR=$(pwd)
ARM_TOOLCHAIN_FILE=$CURRENT_DIR/board/arm-none-eabi-gcc.cmake

cmake_toolchain_dir=$cmake_toolchain_dir"$ARM_GCC_BIN_FOLDER"
cmake_toolchain_file=$cmake_toolchain_file"$ARM_TOOLCHAIN_FILE"
cmake_top_bin_dir=$cmake_top_bin_dir"$CURRENT_DIR/build/$arg_board"
cmake_board_name=$cmake_board_name"$arg_board"
cmake_product_name=$cmake_product_name"$arg_product"
cmake_mcu_name=$cmake_mcu_name"$arg_mcu"
cmake_build_type=$cmake_build_type"Debug"
cmake_test_bool=$cmake_test_bool"True"

# check for help
for var in "$@"; do
    case $var in
    -h | -\? | --help)
        usage
        exit 0
        ;;
    unit)
        arg_board="unit"
        cmake_args="$cmake_build_type $cmake_test_bool"
        ;;
    *)
        product_exists=false
        for dir in product/*/; do
            product=$(basename "$dir")
            if [ "$product" == "$arg_product" ]; then
                product_exists=true
            fi
        done

        if [ "$product_exists" = false ]; then
            echo "PRODUCT DOES NOT EXIST"
            usage
            exit 0
        fi

        board_exists=false
        for dir in product/$product/board/*/; do
            board=$(basename "$dir")
            if [ "$board" == "$arg_board" ]; then
                board_exists=true
            fi
        done

        if [ "$board_exists" = false ]; then
            echo "BOARD DOES NOT EXIST"
            usage
            exit 0
        fi
        cmake_args="$cmake_toolchain_dir $cmake_toolchain_file $cmake_top_bin_dir $cmake_board_name $cmake_product_name $cmake_mcu_name"
        ;;
    esac
done

sh generate_vscode_launch_file.sh
rm -rf $CURRENT_DIR/build/$arg_board/$arg_product
mkdir -p $CURRENT_DIR/build/$arg_board/$arg_product
cd $CURRENT_DIR/build/$arg_board/$arg_product
cmake -G "Unix Makefiles" $cmake_args $CURRENT_DIR
make -j8
