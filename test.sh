#!/bin/bash
cd luajit
make CROSS="arm-none-eabi-" TARGET_CFLAGS="-mcpu=cortex-m3  -mfloat-abi=softfp"
