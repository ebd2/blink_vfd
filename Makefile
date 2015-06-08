BIN=blink_vfd
OBJS=blink_vfd.o

MCU=atmega328
PROGRAMMER=usbtiny

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=1000000UL -mmcu=$(MCU)
LDFLAGS=-Os -mmcu=$(MCU)

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

install: $(BIN).hex
	sudo avrdude -V -c $(PROGRAMMER) -p $(MCU)  -U flash:w:$<

.PHONY: clean
clean:
	-rm -f $(BIN).elf $(BIN).hex $(OBJS)
