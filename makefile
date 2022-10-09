# windows MinGW32-make all to make include and src files
# windows MinGW32-make output to generate run.exe

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

CC = g++
CFLAGS  = -c -Wall -I.
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-window -lsfml-system

SRCS = $(SRC_DIR)/ingredient.cpp $(SRC_DIR)/recipe.cpp $(SRC_DIR)/file_manager.cpp
OBJS = $(OBJ_DIR)/ingredient.o $(OBJ_DIR)/recipe.o $(OBJ_DIR)/file_manager.o

DEPS = $(INC_DIR)/ingredient.h $(INC_DIR)/recipe.h $(INC_DIR)/food_component.h $(INC_DIR)/file_manager.h

# .PHONY: all build clean

all: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)/Trace.o: $(DEPS)

# VPATH=src:include
# CFLAGS=-I src:include

# run.exe to run main
output: $(SRC_DIR)/main.cpp $(OBJS)
	g++ -o run $(SRC_DIR)/main.cpp $(DEPS) $(OBJS) $(LDFLAGS)

# recipe.o: recipe.cpp
# 	g++ -c recipe.cpp

build:
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJS) run

fresh: clean build all output