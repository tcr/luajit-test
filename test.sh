#!/bin/bash
cd luajit
make HOST_CC="gcc -m32" CROSS="arm-none-eabi-" TARGET_SYS=Other TARGET_CFLAGS="-mcpu=cortex-m3 -mthumb -mfloat-abi=softfp"
