all:
	arm-none-eabi-gcc -mthumb -march=armv7 -mfix-cortex-m3-ldrd -T lm3s6965.ld main.c reset.S syscalls.c -o main -O3
	arm-none-eabi-objcopy -O binary main main.bin
	qemu-system-arm -M lm3s6965evb --kernel main.bin --serial stdio

dump:
	arm-none-eabi-objdump -d -S main | awk '/test>:/' RS=