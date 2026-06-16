CC = gcc

TARGET = joke-fetcher

SRC := $(wildcard src/*.c)

LINKER = -lcurl -lcjson

CFLAGS = -Wall -Iinclude -Wextra

RELEASE = -O3 -s

.PHONY: all clean release

all:
	$(CC) $(CFLAGS) $(SRC) $(LINKER) -o $(TARGET)

clean:
	rm -f $(TARGET)

release:
	$(CC) $(CFLAGS) $(RELEASE) $(SRC) $(LINKER) -o $(TARGET)