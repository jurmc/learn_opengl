G++ = g++
LD = ld
CFLAGS = -I glm_prefix/include/
LDFLAGS = -lraylib

sources = start.cpp \
	  axes.cpp \
	  dot_product.cpp \
	  cross_product.cpp \
	  mat_operations.cpp

objects = $(sources:.cpp=.o)
executables = $(objects:.o=$(BIN))

all: $(executables)

$(objects): %.o: %.cpp
	$(G++) $(CFLAGS) -c -o $@ $<

$(executables): %$(BIN): %.o
	$(G++) $(LDFLAGS) -o $@ $^

clean:
	rm -rf $(objects)
	rm -rf $(executables)
