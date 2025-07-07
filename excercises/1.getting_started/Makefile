G++ = g++
LD = ld
CFLAGS = -I ../../deps/usr/local/include
VPATH = src
BIN =

sources = triangle1.cpp triangle2-shaders.cpp triangle2-shaders-more-attrs.cpp triangle2-shaders-uniforms.cpp
objects = $(sources:.cpp=.o)
executables = $(objects:.o=$(BIN))

all: $(executables)

$(objects): %.o: %.cpp
	$(G++) $(CFLAGS) -c -o $@ $<

$(executables): %$(BIN): %.o glad.o
	$(G++) -lglfw -o $@ $^

glad.o: glad.c
	$(G++) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf glad.o $(objects)
	rm -rf $(executables)

