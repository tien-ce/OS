TARGET = seqlock
CC = gcc
CFLAGS = -pthread -Wall -Wextra -O2
SRCS = seqlock.c
OBJS = $(SRCS:.c=.o)
HEADERS = seqlock.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
