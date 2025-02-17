CC = gcc
CFLAGS = -Wextra -Wall -pedantic

main: main.o
	$(CC) $(CLFAGS) -o main main.o

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

clean:
	rm *.o main

rebuild: clean main