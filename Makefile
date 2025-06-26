TARGET = main

SRC = main.c boid.c utils.c slider.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lraylib -lm

.PHONY: run, clean

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
