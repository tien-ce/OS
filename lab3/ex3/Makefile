# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread -g

# Executable name
EXEC = logbuf
# Source files
SRCS = logbuf.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)
