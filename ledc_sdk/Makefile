cross_compile 	?= arm-linux-gnueabihf-
name			?= ledc
cflags 			?= -I../include

gcc				:= $(cross_compile)gcc
ld 				:= $(cross_compile)ld
objcopy 		:= $(cross_compile)objcopy
objdump 		:= $(cross_compile)objdump

objs	:= start.o main.o

$(name).bin : $(objs)
	$(ld) -Timx6ull.lds -o $(name).elf $^
	$(objcopy) -O binary -S $(name).elf $@
	$(objdump) -D -m arm $(name).elf > $(name).dis
	
%.o : %.c
	$(gcc) $(cflags) -Wall -nostdlib -c -o2 -o $@ $<
%.o : %.s
	$(gcc) $(cflags) -Wall -nostdlib -c -o2 -o $@ $<
	
clean:
	rm -rf *.o $(name).bin $(name).elf $(name).dis