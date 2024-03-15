CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEPS = main.h err.h fifo.h lifo.h
OBJ = main.o err.o lifo.o fifo.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) program