# Project Compilation Guide

This README outlines the process for using the provided Makefile to automate the compilation of an autograder program and multiple instances of a template program. The Makefile enables the efficient creation of a specified number of template program binaries.

## Prerequisites

Before proceeding, ensure the following tools are installed and accessible from your command line or terminal:

- **GNU Make**
- **GCC (GNU Compiler Collection)**

## File Structure

- **`autograder.c`**: Source code for the autograder program.
- **`template.c`**: Source code for the template program. This will be compiled into multiple binaries.

## Makefile Overview

### Variables

- **`CC`**: Specifies the compiler, defaulting to `gcc`.
- **`CFLAGS`**: Compiler flags for the compilation process. Defaults to `-Wall` (for all warnings) and `-g` (for debugging information).
- **`SOURCE_FILE`**: The source file for the template program, defaulting to `template.c`.
- **`SOL_DIR`**: The directory where compiled template binaries will be placed, defaulting to `./solutions`.

### Targets

- **`all`**: The default target that compiles both the autograder and the specified number of template binaries.
- **`autograder`**: Compiles the autograder program.
- **`clean`**: Removes all compiled binaries and the autograder executable.

## Usage

### Compile Everything

To compile the autograder:

```bash
make
```

### Clean Compiled Files

To remove default number of template binaries:

```bash
make clean
```

