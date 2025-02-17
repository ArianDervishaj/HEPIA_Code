CC:=gcc
CFLAG:=-Wall -Wextra -std=gnu11
LFLAG:= -lpthread

ex1: ex1.o
	$(CC) $(CFLAG) ex1.o $(LFLAG) -o ex1.out

ex1.o: ex1.c
	$(CC) $(CFLAG) -c ex1.c -o ex1.o

ex2: ex2.o
	$(CC) $(CFLAG) ex2.o $(LFLAG) -o ex2.out

ex2.o: ex2.c
	$(CC) $(CFLAG) -c ex2.c -o ex2.o

ex3: ex3.o
	$(CC) $(CFLAG) ex3.o $(LFLAG) -o ex3.out

ex3.o: ex3.c
	$(CC) $(CFLAG) -c ex3.c -o ex3.o

ex4: ex4.o
	$(CC) $(CFLAG) ex4.o $(LFLAG) -o ex4.out

ex4.o: ex4.c
	$(CC) $(CFLAG) -c ex4.c -o ex4.o
clean:
	rm -f *.o *.out