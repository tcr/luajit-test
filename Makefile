all: build

build: 
	cd test; luajit ../luajit/dynasm/dynasm.lua main.dasc > main.c
	cd test; export PATH=/Users/tim/Developer/Cross/arm-cs-tools-2012.03-56-e3f4013-20130610/bin:$(PATH); arm-none-eabi-gcc -mthumb -gdwarf-2 -fno-inline-small-functions -march=armv7 -mfix-cortex-m3-ldrd -T ../inc/lm3s6965.ld ./main.c ../inc/reset.S ../inc/syscalls.c -I../luajit/dynasm -o main -O1 -std=c99 -Idynasm -DDASM_VERSION=10300 -Wno-overflow 
	cd test; export PATH=/Users/tim/Developer/Cross/arm-cs-tools-2012.03-56-e3f4013-20130610/bin:$(PATH); arm-none-eabi-objcopy -O binary main main.bin 

biggy:
	cd test; luajit ../luajit/dynasm/dynasm.lua biggy.dasc > biggy.c

run: build
	cd test; node run | tee | egrep "^;;; " | tee a.txt

test: build
	@cd test; echo "\n\n\n\n\n\n"
	@cd test; node run

debug: build
	cd test; qemu-system-arm -M lm3s6965evb -s -S --kernel main.bin --serial stdio

dump: build
	cd test; node dump.js fib | tee b.txt

clean:
	cd test; rm *.bin main

thumb:
	cd luajit ;\
		make clean ;\
		make HOST_CC="gcc-4.9 -m32" CROSS="arm-none-eabi-" TARGET_SYS=Other TARGET_CFLAGS="-mcpu=cortex-m3 -mthumb -mfloat-abi=softfp" TARGET_SYS=arm

arm:
	cd luajit ;\
		make clean ;\
		make HOST_CC="gcc-4.9 -m32" CROSS="arm-none-eabi-" TARGET_CFLAGS="-mfloat-abi=soft" TARGET_SYS=arm
