all: build

build:
	# luajit dynasm/dynasm.lua main.dasc > main.c
	arm-none-eabi-gcc -mthumb -gdwarf-2 -fno-inline-small-functions -march=armv7 -mfix-cortex-m3-ldrd -T ../inc/lm3s6965.ld ./main.c ../inc/reset.S ../inc/syscalls.c -I../dynasm -o main -O1 -std=c99 -Idynasm -DDASM_VERSION=10300
	arm-none-eabi-objcopy -O binary main main.bin

run: build
	qemu-system-arm -M lm3s6965evb --kernel main.bin --serial stdio

debug: build
	qemu-system-arm -M lm3s6965evb -s -S --kernel main.bin --serial stdio

dump:
	arm-none-eabi-objdump -d -S main | awk '/test>:/' RS=

clean:
	rm *.bin main