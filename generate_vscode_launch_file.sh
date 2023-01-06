#!/bin/bash

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
