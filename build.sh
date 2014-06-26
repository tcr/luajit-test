#!/bin/bash

rm -rf stage || true
mkdir -p stage || true
luajit ./luajit/dynasm/dynasm.lua "$1" > stage/main.c
arm-none-eabi-gcc -mthumb -gdwarf-2 -fno-inline-small-functions -march=armv7-m -msoft-float -mfix-cortex-m3-ldrd \
  -std=c99 -Idynasm -DDASM_VERSION=10300 -Wno-overflow -O1 \
  -I./luajit/dynasm -I ./test -o ./stage/main \
  -T ./inc/lm3s6965.ld ./stage/main.c ./inc/startup_lpc1800.s ./inc/startup.c ./inc/syscalls.c
arm-none-eabi-objcopy -O binary stage/main stage/main.bin
