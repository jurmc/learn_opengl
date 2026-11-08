SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SHDR_SRC_DIR := shdr_src
SHDR_GEN_DIR := shdr_gen

TARGET = $(BIN_DIR)/sokol_hello

CC := gcc
CFLAGS := -MP -MMD -I include -I ../sokol -I ../sokol-samples/ -I $(SHDR_GEN_DIR)/
LDFLAGS := -ggdb -lm -lX11 -lXi -lGL -lXcursor -lglfw

SHDC := ../sokol-tools/.fibs/dist/linux-make-release/sokol-shdc
SHDC_FLAGS = -l glsl430

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

SHDR_SRCS := $(wildcard $(SHDR_SRC_DIR)/*.glsl)
SHDR_GEN := $(patsubst $(SHDR_SRC_DIR)/%.glsl, $(SHDR_GEN_DIR)/%.glsl.h, $(SHDR_SRCS))

all: $(TARGET)

$(TARGET): $(SHDR_GEN) $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(SHDR_GEN_DIR)/%.glsl.h: $(SHDR_SRC_DIR)/%.glsl | $(SHDR_GEN_DIR)
	$(SHDC) $(SHDC_FLAGS) -i $< -o $@

-include $(DEPS)

$(OBJ_DIR) $(SHDR_GEN_DIR) $(BIN_DIR):
	mkdir -p $@

.PHONY clean:
	rm -rf $(OBJ_DIR) $(SHDR_GEN_DIR) $(BIN_DIR)
