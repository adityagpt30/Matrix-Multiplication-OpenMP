CC=gcc
TARGET=main

CFLAGS = -Wall -fopenmp
all:	main.o MMultiplication.o
	$(CC) $(CFLAGS) main.c MMultiplication.c -o $(TARGET)

clean:
	rm *.o $(TARGET)