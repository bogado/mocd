# Uncomment the lines below if you have problems with $PATH
#SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)

all:
	platformio -f -c vim run | tail -n -1

upload: all
	platformio -f -c vim run --target upload

clean:
	platformio -f -c vim run --target clean

program:
	platformio -f -c vim run --target program

uploadfs:
	platformio -f -c vim run --target uploadfs

update:
	platformio -f -c vim update

monitor: upload
	platformio -f -c vim device monitor --baud 115200

build:
	mkdir build build/tmp


