CC = gcc
CFLAGS =  -g -Wall -Wextra

main: Serie1.o
	$(CC) $(CFLAGS) -o main.out Serie1.o -lm

Serie1.o: Serie1.c Serie1.h
	$(CC) $(CFLAGS) -c Serie1.c

clean:
	rm *.o *.out