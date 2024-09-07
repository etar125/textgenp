CC = g++
CFLAGS = -Os -ffunction-sections -Wall -Wl,--gc-sections,--strip-all -fno-asynchronous-unwind-tables -fpermissive

default: build

build: src/main.cpp
	mkdir -p bin
	$(CC) src/main.cpp -o bin/textgenp $(CFLAGS)
	
clean:
	rm -rf $(wildcard bin/*)

rebuild: clean build
