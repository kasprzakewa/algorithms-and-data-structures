CC = gcc
CFLAGS = -Wall -Wextra -std=c11
DEPS = main.h err.h list.h
OBJ = main.o err.o list.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) program