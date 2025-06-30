TARGET = main

CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lraylib -lm

run: $(TARGET)
	./$(TARGET)

main: main.o boid.o utils.o slider.o
	$(CC) main.o boid.o utils.o slider.o -o $(TARGET) $(CFLAGS) $(LDFLAGS)

main.o: main.c boid.h utils.h slider.h
	$(CC) -c main.c $(CFLAGS)

boid.o: boid.c boid.h utils.h
	$(CC) -c boid.c $(CFLAGS)

utils.o: utils.c  utils.h
	$(CC) -c utils.c $(CFLAGS)

slider.o: slider.c slider.h
	$(CC) -c slider.c $(CFLAGS)

clean:
	rm -f *.o $(TARGET)
