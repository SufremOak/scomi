CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99 -g -lncurses -lmenu -lform -lpanel
TARGET := scomi.bin
LDLIBS := -lncurses -lmenu -lform -lpanel
TARG := $(TARGET).tar.gz
SRCS := $(wildcard main.c)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(TARGET)

dist: $(TARG)

$(TARG): $(TARGET)
	tar -czvf $@ $^

install:
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)
