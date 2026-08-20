# bear -- g++ -std=c++23 -lassimp assimp_intro.cpp -o assimp_intro && ./assimp_intro
G++ = g++
LD = ld
CFLAGS = -std=c++23 -I ../deps/usr/local/include
VPATH = src
BIN =

sources = \
   assimp_intro.cpp \
   triangle.cpp

objects = $(sources:.cpp=.o)
executables = $(objects:.o=$(BIN))

all: $(executables)

$(objects): %.o: %.cpp
	$(G++) $(CFLAGS) -c -o $@ $<

$(executables): %$(BIN): %.o
	$(G++) -L ../deps/usr/local/lib -o $@ $^ -lassimp -lglfw -l:glad.a

clean:
	rm -rf $(objects)
	rm -rf $(executables)

