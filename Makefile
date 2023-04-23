# This is a Makefile to build and
# run the Chada Tech Corner Grocer program.

# Date: 2023 APR 016
# Author: Dennis James Stelmach

all: build

build: main.cpp FrequencyCounter.cpp FrequencyCounter.h
	g++ -Wall -o main main.cpp FrequencyCounter.cpp

run: build
	./main

clean:
	rm -f main frequency.dat
