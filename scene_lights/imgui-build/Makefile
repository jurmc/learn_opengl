CXX = g++
CXXFLAGS = -ggdb -std=c++23 -Wall -Wextra -MMD -MP -I ../imgui -I ../imgui/backends
#-I ../deps/usr/local/include

#LDFLAGS = -L ../deps/usr/local/lib

LIBS = -l:glad.a -lglfw -lGL

OBJ_DIR := ./

VPATH  =  ../imgui/ ../imgui/backends/

SOURCES := imgui.cpp \
	imgui_tables.cpp \
	imgui_draw.cpp \
	imgui_widgets.cpp \
	imgui_impl_glfw.cpp \
	imgui_impl_opengl3.cpp

OBJECTS = $(SOURCES:.cpp=.o)
DEPS    = $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJECTS) $(DEPS)
