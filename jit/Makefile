all: build

build: 
	#luajit ../dynasm/dynasm.lua main.dasc > main.c
	export PATH=/Users/tim/Developer/Cross/arm-cs-tools-2012.03-56-e3f4013-20130610/bin:$(PATH); arm-none-eabi-gcc -mthumb -gdwarf-2 -fno-inline-small-functions -march=armv7 -mfix-cortex-m3-ldrd -T ../inc/lm3s6965.ld ./main.c ../inc/reset.S ../inc/syscalls.c -I../dynasm -o main -O1 -std=c99 -Idynasm -DDASM_VERSION=10300
	export PATH=/Users/tim/Developer/Cross/arm-cs-tools-2012.03-56-e3f4013-20130610/bin:$(PATH); arm-none-eabi-objcopy -O binary main main.bin

run: build
	@node run | egrep "^;;; " > b.txt

debug: build
	qemu-system-arm -M lm3s6965evb -s -S --kernel main.bin --serial stdio

dump:
	@node dump.js > a.txt

clean:
	rm *.bin main