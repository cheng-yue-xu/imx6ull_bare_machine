cross_compile 	?= arm-linux-gnueabihf-
name			?= int

gcc				:= $(cross_compile)gcc
ld 				:= $(cross_compile)ld
objcopy 		:= $(cross_compile)objcopy
objdump 		:= $(cross_compile)objdump

libpath     	:= -lgcc -L /usr/local/arm/gcc-linaro-13.0.0-2022.10-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/13.0.0

includedir		:= include \
				   bsp/include \
				   stdio/include \
				   project

sourcedir		:= project \
				   stdio/lib \
				   bsp	  

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
	$(ld) -Timx6ull.lds -o $(name).elf $^ $(libpath)
	$(objcopy) -O binary -S $(name).elf $@
	$(objdump) -D -m arm $(name).elf > $(name).dis
	
$(sobjs) : obj/%.o : %.s
	$(gcc) -Wall -nostdlib -fno-builtin -c -o2 $(inclued) -o $@ $<
	
$(cobjs) : obj/%.o : %.c
	$(gcc) -Wall -nostdlib -fno-builtin -Wa,-mimplicit-it=thumb -c -o2 $(inclued) -o $@ $<
	
clean:
	rm -rf $(sobjs) $(cobjs) $(name).bin $(name).elf $(name).dis
