###############################################################################
# Makefile for the project Pjt14_I2C_TCN75
###############################################################################

## General Flags
PROJECT = Pjt14_I2C_TCN75
MCU = atmega2560
TARGET = Pjt14_I2C_TCN75.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=7372800UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Pjt14_I2C_TCN75.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = adc_tc1047.o app_linked_list.o app_prime.o app_sum.o cir_queue.o led.o linked_list.o main.o spi_tc77.o task.o timer_linked_list.o uart.o i2c_tcn75.o app_watch.o app_rand.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Pjt14_I2C_TCN75.hex Pjt14_I2C_TCN75.eep Pjt14_I2C_TCN75.lss size

## Compile
adc_tc1047.o: ../adc_tc1047.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

app_linked_list.o: ../app_linked_list.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

app_prime.o: ../app_prime.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

app_sum.o: ../app_sum.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

cir_queue.o: ../cir_queue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

led.o: ../led.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

linked_list.o: ../linked_list.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

spi_tc77.o: ../spi_tc77.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

task.o: ../task.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer_linked_list.o: ../timer_linked_list.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

i2c_tcn75.o: ../i2c_tcn75.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

app_watch.o: ../app_watch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

app_rand.o: ../app_rand.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Pjt14_I2C_TCN75.elf dep/* Pjt14_I2C_TCN75.hex Pjt14_I2C_TCN75.eep Pjt14_I2C_TCN75.lss Pjt14_I2C_TCN75.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

