CC=arm-none-eabi-gcc
MACH=cortex-m4
LINKER_SCRIPT=nrf52_ld.ld
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T nrf52_ls.ld -Wl,-Map=Build/final.map
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I Inc/
INCLUDES+= -I ../drivers/Inc/ 
INCLUDES+= -I ../shared/Inc/



############################################
# Source files

OBJS		+= Build/main.o
OBJS		+= Build/nrf52_startup.o
OBJS		+= Build/syscalls.o

OBJS		+= Build/driver_gpio.o
OBJS		+= Build/driver_systick.o
OBJS		+= Build/driver_uart.o

OBJS		+= Build/system.o

all: Build/final.elf

Build/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).c

Build/%.o: ../drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o ../drivers/Src/$(*).c

Build/%.o: ../shared/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o ../shared/Src/$(*).c

Build/nrf52_startup.o: nrf52_startup.c
	$(CC) $(CFLAGS) -o $@ $^ 

Build/final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary Build/final.elf Build/flash.bin
	$(OBJCOPY) -O binary Build/final.elf ~/opt/SEGGER/flash.bin


clean:
	rm -rf *.o *.map Build/*.o