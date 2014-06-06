#!/bin/bash
cd luajit
make clean
make HOST_CC="gcc-4.9 -m32" CROSS="arm-none-eabi-" TARGET_SYS=Other TARGET_CFLAGS="-mcpu=cortex-m3 -mthumb -mfloat-abi=softfp" TARGET_SYS=arm
