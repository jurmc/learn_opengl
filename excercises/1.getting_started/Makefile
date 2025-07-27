G++ = g++
LD = ld
CFLAGS = -I ../../deps/usr/local/include -I ../../utils/include -I glm_raylib_sandbox/glm_prefix/include/
VPATH = src
BIN =

sources = \
   triangle1.cpp \
   triangle2-shaders.cpp \
   triangle2-shaders-more-attrs.cpp \
   triangle2-shaders-uniforms.cpp \
   triangle3.cpp \
   textures1.cpp \
   textures1-ex1.cpp \
   textures1-ex3.cpp \
   textures1-ex4.cpp \
   textures2.cpp \
   textures2-ex2.cpp \
   textures3-going3d.cpp \
   textures3-more3d.cpp \
   textures3-ten-cubes.cpp \
   minecraft-cubes.cpp \
   camera1.cpp

objects = $(sources:.cpp=.o)
executables = $(objects:.o=$(BIN))

all: $(executables)

$(objects): %.o: %.cpp
	$(G++) $(CFLAGS) -c -o $@ $<

$(executables): %$(BIN): %.o
	$(G++) -L ../../deps/usr/local/lib -o $@ $^ -lglfw -l:glad.a

clean:
	rm -rf $(objects)
	rm -rf $(executables)

