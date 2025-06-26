# gcc shooter.c -lncurses -ltinfo

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -D_DEFAULT_SOURCE
LDFLAGS = -lncurses -ltinfo

# Target and source files
TARGET = shooter
SRC = shooter.c

# Default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean up build files
clean:
	rm -f $(TARGET)
