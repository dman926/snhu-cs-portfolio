# Date: 2023 JUNE 14
# Author: Dennis James Stelmach

all: build

build: Stelmach_CS300_Project_Two.cpp
	g++ -Wall -o main Stelmach_CS300_Project_Two.cpp

run: build
	./main

clean:
	rm -f main
