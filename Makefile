CC = gcc

TARGET = joke-fetcher

SRC := $(wildcard src/*.c)

LINKER = -lcurl -lcjson

CFLAGS = -Wall -Iinclude

RELEASE = -O3 -s

all:
	$(CC) $(CFLAGS) $(SRC) $(LINKER) -o $(TARGET)

clean:
	rm -f $(TARGET)

release:
	$(CC) $(CFLAGS) $(RELEASE) $(SRC) $(LINKER) -o $(TARGET)