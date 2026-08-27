CXX = g++
CXXFLAGS = -ggdb -std=c++23 -Wall -Wextra -MMD -MP -I ../deps/usr/local/include
LDFLAGS = -L ../deps/usr/local/lib

LIBS = -l:glad.a -l:imgui.a -lassimp -lglfw -lGL

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/browser
SRCS   := $(wildcard $(SRC_DIR)/*.cpp)
OBJS   := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
#DEPS   := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.d, $(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

