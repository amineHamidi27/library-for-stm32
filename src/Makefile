PROJECT =  ledBLink1
PROJECT_DIR = /home/amine/Desktop/stm32_workspace/prepaExam
LIBOPENCM3_DIR = /home/amine/Desktop/stm32_workspace/RS232_communication/libopencm3
SRC = main.c $(PROJECT_DIR)/lib/config_gpio/easy_gpio.c \
      
MCU = stm32f103c8t6
ARCH_FLAGS = -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd

CFLAGS = -O2 -Wall \
         $(ARCH_FLAGS) \
         -I$(LIBOPENCM3_DIR)/include \
         -DSTM32F1 \
         -I../lib/config_gpio \
         
         

LDFLAGS = $(ARCH_FLAGS) -nostartfiles \
          -T /home/amine/Desktop/stm32_workspace/tp_comunication/stm32f1.ld \
          -Wl,--gc-sections 

LDLIBS = -lopencm3_stm32f1

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

all: $(PROJECT).bin


$(PROJECT).elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -L$(LIBOPENCM3_DIR)/lib $(LDLIBS) -lc -lgcc
	$(SIZE) $@

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

flash: $(PROJECT).bin
# st-flash write $(PROJECT).bin 0x08000000
	sudo stm32flash.sh -w $(PROJECT).bin /dev/ttyUSB0

clean:
	rm -f *.o *.elf *.bin