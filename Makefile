# Makefile

# Variables
CC=gcc
CFLAGS=-Wall -g -Wno-unused-variable
SOURCE_FILE=template.c
SOL_DIR=./solutions
LETTERS=a b c d e f g h i j k l k l m n o p q r s t
BINARIES=$(addsuffix _sol, $(addprefix $(SOL_DIR)/, $(LETTERS)))

# Default target
all: autograder

# Compile autograder
autograder: autograder.c
	$(CC) $(CFLAGS) -o $@ $^

# Compile template.c into binaries named a_sol, b_sol, c_sol, etc.
# Target to generate all solution binaries
solutions: $(BINARIES)
$(SOL_DIR)/%_sol: $(SOURCE_FILE)
	mkdir -p $(SOL_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Clean the build
clean:
	rm -f autograder

.PHONY: all clean
