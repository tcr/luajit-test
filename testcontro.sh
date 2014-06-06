#!/bin/bash
cd luajit
make clean
make HOST_CC="gcc-4.9 -m32" CROSS="arm-none-eabi-" TARGET_CFLAGS="-mfloat-abi=soft" TARGET_SYS=arm