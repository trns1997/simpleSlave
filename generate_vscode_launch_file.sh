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

workspaceRoot=$(pwd)

test -f .vscode/launch.json && rm .vscode/launch.json

cat <<EOT >>.vscode/launch.json
{
  "version": "0.2.0",
  "configurations": [
EOT
for dir in product/*/; do
    product=$(basename "$dir")
    for dir in product/$product/board/*/; do
        board=$(basename "$dir")
        cat <<EOT >>.vscode/launch.json
    {
      "name": "Debug $product on $board",
      "type": "cortex-debug",
      "request": "launch",
      "cwd": "$workspaceRoot",
      "executable": "$workspaceRoot/build/$board/$product/$product.elf",
      "servertype": "jlink",
      "device": "XMC4800-2048",
      "interface": "swd",
      "runToEntryPoint": "main",
      "breakAfterReset": true,
      "svdFile": "$workspaceRoot/board/xmc/common/XMC4800.svd",
      "armToolchainPath": "$ARM_GCC_BIN_FOLDER"
      ,"showDevDebugOutput": "raw"
    },
EOT
    done
done
cat <<EOT >>.vscode/launch.json
  ]
}
EOT
