objs = start.o main.o
ledc.bin : $(objs)
	arm-linux-gnueabihf-ld -Timx6ull.lds $^ -o ledc.elf
	arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis
	
%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o2 -o $@ $<
%.o : %.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o2 -o $@ $<
clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis