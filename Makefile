BIN=blink_vfd
OBJS=blink_vfd.o

PROCESSOR=atmega328
PROGRAMMER=usbtiny

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=1000000UL -mmcu=$(PROCESSOR)
LDFLAGS=-Os -DF_CPU=1000000UL -mmcu=$(PROCESSOR)

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

install: $(BIN).hex
	sudo avrdude -V -c $(PROGRAMMER) -p $(PROCESSOR)  -U flash:w:$<

clean:
	rm -f $(BIN).elf $(BIN).hex $(OBJS)
