VPATH = src

all: main

main: main.o glad.o
	g++ -lglfw glad.o main.o -o main

main.o: main.cpp
	g++ -I./include -c -o $@ $<

glad.o: glad.c
	g++ -I./include -c -o $@ $<

clean:
	rm -rf glad.o main.o main
