TARGET = main 

CC = gcc
CFLAGS = -Wall -std=c99 -O2
LDFLAGS = -lraylib -lm

run: $(TARGET)
	./$(TARGET)

$(TARGET): main.o boid.o utils.o slider.o dynamic_array.o quadtree.o
	$(CC) main.o boid.o utils.o slider.o dynamic_array.o quadtree.o -o $(TARGET) $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

boid.o: boid.c boid.h utils.h
	$(CC) -c boid.c $(CFLAGS)

utils.o: utils.c  utils.h
	$(CC) -c utils.c $(CFLAGS)

dynamic_array.o: dynamic_array.c dynamic_array.h
	$(CC) -c dynamic_array.c $(CFLAGS)

slider.o: slider.c slider.h
	$(CC) -c slider.c $(CFLAGS)

quadtree.o: quadtree.c quadtree.h dynamic_array.h
	$(CC) -c quadtree.c $(CFLAGS)

clean:
	rm -f *.o $(TARGET)
