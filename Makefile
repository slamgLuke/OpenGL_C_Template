CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
LINKER_FLAGS = -lGL -lglfw -lGLEW -lcglm

SRC_DIR = src
BIN_DIR = bin

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/shaderLoader.c $(SRC_DIR)/initWindow.c
EXEC = $(BIN_DIR)/exec

buildrun: $(SRCS)
		@echo "------------------------"
		@echo "> BUILDING AND RUNNING"
		@echo "------------------------"
		mkdir -p $(BIN_DIR)
		@echo "> make: Compiling $(SRCS)..."
		$(CC) $(CFLAGS) -g -o $(EXEC) $(SRCS) $(LINKER_FLAGS)
		@echo "------------------------"
		@echo "> make: Done Compiling!  [1/2]"
		@echo "------------------------"
		@echo "> make: Running $(EXEC)..."
		./$(EXEC)
		@echo "------------------------"
		@echo "> make: Done Running!    [2/2]"
		@echo "------------------------"

build: $(SRCS)
		@echo "------------------------"
		@echo "> BUILDING"
		@echo "------------------------"
		mkdir -p $(BIN_DIR)
		@echo "> make: Compiling $(SRCS)..."
		$(CC) $(CFLAGS) -g -o $(EXEC) $(SRCS) $(LINKER_FLAGS)
		@echo "------------------------"
		@echo "> make: Done Compiling!  [1/1]"
		@echo "------------------------"

run: $(EXEC)
		@echo "------------------------"
		@echo "> RUNNING"
		@echo "------------------------"
		@echo "> make: Running $(EXEC)..."
		./$(EXEC)
		@echo "------------------------"
		@echo "> make: Done Running!    [1/1]"
		@echo "------------------------"

