all: build

build:
	./build.sh test/main.dasc

biggy:
	cd test; luajit ../luajit/dynasm/dynasm.lua biggy.dasc > biggy.c

run: build
	cd test; node run | tee | egrep "^;;; " | tee a.txt

test: build
	TAPV=1 tinytap -e "./dotest.sh" test/*.dasc

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
