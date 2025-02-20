CC=arm-none-eabi-gcc
MACH=cortex-m4
LINKER_SCRIPT=nrf52_ld.ld
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T nrf52_ls.ld -Wl,-Map=build/final.map
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES+= -I app/Inc/
INCLUDES+= -I drivers/Inc/ 
INCLUDES+= -I common/Inc/ 
INCLUDES+= -I bsp/Inc/ 
INCLUDES+= -I shared/Inc/



############################################
# Source files

OBJS		+= build/main.o
OBJS		+= build/init_app.o
OBJS		+= build/nrf52_startup.o
OBJS		+= build/syscalls.o

OBJS		+= build/driver_event.o
OBJS		+= build/driver_interrupt.o
OBJS		+= build/driver_gpio.o
OBJS		+= build/driver_systick.o
OBJS		+= build/driver_uart.o
OBJS		+= build/driver_spi.o
OBJS		+= build/driver_saadc.o

OBJS		+= build/nor.o

COMMON 		+= build/ring-buffer.o



all: build/final.elf

############################################
# Build rules

build/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o Src/$(*).c

build/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o app/Src/$(*).c

build/%.o: drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o drivers/Src/$(*).c

build/%.o: common/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o common/Src/$(*).c

build/%.o: bsp/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o bsp/Src/$(*).c

build/%.o: shared/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o build/$(*).o shared/Src/$(*).c


build/%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^ 

############################################
# Finals

build/final.elf: $(OBJS) $(COMMON)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary build/final.elf build/flash.bin

load: 
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/nrf52.cfg -c init -c "reset init" \
	-c "flash write_image erase build/final.elf" -c "reset run" -c shutdown

reset:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/nrf52.cfg -c init -c "reset run" -c shutdown

clean:
	rm -rf *.o *.map build/*.o