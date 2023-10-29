TARGET := pi.out
SRCS := main.c
OBJS := $(SRCS:.c=.o)
CC := gcc -m64
CFLAGS := -O3 -Wall -pthread

.PHONY: default clean

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
