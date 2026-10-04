CXX = g++
CXXFLAGS = -ggdb -std=c++23 -Wall -Wextra -MMD -MP -I imgui/ -I imgui/backends -I ../deps/usr/local/include
LDFLAGS = -L ../deps/usr/local/lib

LIBS = -l:glad.a -lglfw -lGL -lassimp

SRC_DIR := ./
OBJ_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/scene
SRCS   := $(wildcard $(SRC_DIR)/*.cpp)
OBJS   := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

IMGUI_SOURCES := imgui.cpp \
	imgui_tables.cpp \
	imgui_draw.cpp \
	imgui_widgets.cpp \
	imgui_impl_glfw.cpp \
	imgui_impl_opengl3.cpp
IMGUI_OBJECTS = $(patsubst %.cpp, imgui-build/%.o, $(IMGUI_SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(IMGUI_OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(IMGUI_OBJECTS) $(LDFLAGS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

