CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=gnu11 -fsanitize=address
LFLAG = -lpthread

serie1: serie1.o
	$(CC) $(CFLAGS) serie1.o -o serie1.out $(LFLAG)

serie1.o : serie1.c
	$(CC) $(CFLAGS) -c serie1.c  -o serie1.o

ex2: ex2.o
	$(CC) $(CFLAGS) ex2.o -o ex2.out $(LFLAG)

ex2.o:
	$(CC) $(CFLAGS) -c ex2.c -o ex2.o


ex3: ex3.o
	$(CC) $(CFLAGS) ex3.o -o ex3.out $(LFLAG)

ex3.o:
	$(CC) $(CFLAGS) -c ex3.c -o ex3.o

ex4: ex4.o
	$(CC) $(CFLAGS) ex4.o -o ex4.out $(LFLAG)

ex4.o: ex4.c
	$(CC) $(CFLAGS) -c ex4.c -o ex4.o

clean:
	rm *.o *.out