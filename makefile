# windows MinGW32-make all to make include and src files
# windows MinGW32-make output to generate run.exe

INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj

# UTIL_INC_DIR = include/utility
UTIL_SRC_DIR = src/utility
UTIL_OBJ_DIR = obj/utility

C = g++
CFLAGS  = -c -Wall -I.
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-window -lsfml-system


SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

MAIN_OBJS_ENDING := $(filter-out $(SRC_DIR)/main.o, $(SRCS:%.cpp=%.o))
OBJS := $(MAIN_OBJS_ENDING:$(SRC_DIR)/%=$(OBJ_DIR)/%)

DEPS := $(shell find $(INC_DIR) -name '*.h' -or -name '*.hpp')

# SRCS = $(SRC_DIR)/divisible_ingredient.cpp $(SRC_DIR)/whole_ingredient.cpp $(SRC_DIR)/recipe.cpp $(SRC_DIR)/file_manager.cpp $(SRC_DIR)/food_component.cpp $(UTIL_SRC_DIR)/windowControl.cpp $(UTIL_SRC_DIR)/element.cpp $(UTIL_SRC_DIR)/simpleText.cpp $(UTIL_SRC_DIR)/textInput.cpp $(UTIL_SRC_DIR)/dropdownLayout.cpp
# OBJS = $(OBJ_DIR)/divisible_ingredient.o $(OBJ_DIR)/whole_ingredient.o $(OBJ_DIR)/recipe.o $(OBJ_DIR)/file_manager.o $(OBJ_DIR)/food_component.o $(UTIL_OBJ_DIR)/windowControl.o $(UTIL_OBJ_DIR)/element.o $(UTIL_OBJ_DIR)/simpleText.o $(UTIL_OBJ_DIR)/textInput.o $(UTIL_OBJ_DIR)/dropdownLayout.o
# DEPS = $(INC_DIR)/divisible_ingredient.h $(INC_DIR)/whole_ingredient.h $(INC_DIR)/recipe.h $(INC_DIR)/food_component.h $(INC_DIR)/file_manager.h $(UTIL_INC_DIR)/button.h $(UTIL_INC_DIR)/button.hpp $(UTIL_INC_DIR)/windowControl.h $(UTIL_INC_DIR)/element.h $(UTIL_INC_DIR)/simpleText.h $(UTIL_INC_DIR)/textInput.h $(UTIL_INC_DIR)/dropdownLayout.h

# @echo $(OBJS)
# $(info VAR="$(OBJS)")

# .PHONY: all build clean



functional: $(OBJS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

util:  $(OBJS)
$(OBJ_DIR)/%.o: $(UTIL_SRC_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)/Trace.o: $(DEPS)

# VPATH=src:include
# CFLAGS=-I src:include

# run.exe to run main
output: $(SRC_DIR)/main.cpp $(OBJS) $(DEPS)
	g++ -o run $(SRC_DIR)/main.cpp $(OBJS) $(LDFLAGS)

# recipe.o: recipe.cpp
# 	g++ -c recipe.cpp

build:
	mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR)
	mkdir -p $(UTIL_OBJ_DIR)
	cd ..

clean:
	rm -rf $(OBJS) run

fresh: clean build functional util output