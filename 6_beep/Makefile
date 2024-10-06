cross_compile 	?= arm-linux-gnueabihf-
name			?= beep

gcc				:= $(cross_compile)gcc
ld 				:= $(cross_compile)ld
objcopy 		:= $(cross_compile)objcopy
objdump 		:= $(cross_compile)objdump

includedir		:= include \
				   bsp/clk \
				   bsp/beep \
				   bsp/delay \
				   project

sourcedir		:= project \
				   bsp/clk \
				   bsp/beep \
				   bsp/delay 	  

inclued			:= $(patsubst %, -I%, $(includedir))

sfiles	    	:= $(foreach dir, $(sourcedir), $(wildcard $(dir)/*.s))
cfiles	    	:= $(foreach dir, $(sourcedir), $(wildcard $(dir)/*.c))

sfilesndir		:= $(notdir $(sfiles))
cfilesndir		:= $(notdir $(cfiles))

sobjs			:= $(patsubst %, obj/%, $(sfilesndir:.s=.o))
cobjs			:= $(patsubst %, obj/%, $(cfilesndir:.c=.o))

objs			:= $(sobjs) $(cobjs)

VPATH			:= $(sourcedir)

.PHONY:clean

$(name).bin : $(objs)
	$(ld) -Timx6ull.lds -o $(name).elf $^
	$(objcopy) -O binary -S $(name).elf $@
	$(objdump) -D -m arm $(name).elf > $(name).dis
	
$(sobjs) : obj/%.o : %.s
	$(gcc) -Wall -nostdlib -c -o2 $(inclued) -o $@ $<
	
$(cobjs) : obj/%.o : %.c
	$(gcc) -Wall -nostdlib -c -o2 $(inclued) -o $@ $<
	
clean:
	rm -rf $(sobjs) $(cobjs) $(name).bin $(name).elf $(name).dis
