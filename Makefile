all: main

main: main.o glad.o
	g++ -lglfw glad.o main.o -o main

main.o: main.cpp
	g++ -I./include -c -o main.o main.cpp

glad.o: src/glad.c
	g++ -I./include -c -o glad.o src/glad.c

clean:
	rm -rf glad.o main.o main
