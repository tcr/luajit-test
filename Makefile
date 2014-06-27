all: build

build:

client: thumb
	arm-none-eabi-gcc -mthumb -gdwarf-2 -ggdb -fno-inline-small-functions -march=armv7-m -msoft-float -mfix-cortex-m3-ldrd \
		-std=c99 -Idynasm -DDASM_VERSION=10300 -Wno-overflow -O1 \
		-I./luajit/dynasm -I ./client -o ./client/main \
		-T ./inc/lm3s6965.ld ./client/main.c ./inc/startup_lpc1800.s ./inc/startup.c ./inc/syscalls.c \
		-I./luajit/src ./luajit/src/libluajit.a -lm
	arm-none-eabi-objcopy -O binary client/main client/main.bin
	./run.js client/main.bin -d

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
		make HOST_CC="gcc-4.9 -m32 -ggdb" CROSS="arm-none-eabi-" TARGET_SYS=Other TARGET_CFLAGS="-mcpu=cortex-m3 -mthumb -mfloat-abi=softfp" TARGET_SYS=arm

thumb-clean:
	cd luajit ;\
		make clean

arm:
	cd luajit ;\
		make clean ;\
		make HOST_CC="gcc-4.9 -m32" CROSS="arm-none-eabi-" TARGET_CFLAGS="-mfloat-abi=soft" TARGET_SYS=arm
