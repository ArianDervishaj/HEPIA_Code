CC:= gcc
CFLAG:=-Wall -Wextra -std=gnu11
LFLAG:=  -lm -lpthread

ex2: ex2.o
	$(CC) $(CFLAG) ex2.o $(LFLAG) -o ex2.out 

ex2.o:
	$(CC) $(CFLAG) ex2.c -c ex2.o 

barriere1: barriere1.o
	$(CC) $(CFLAG) barriere1.o $(LFLAG) -o barriere1.out 

barriere1.o:
	$(CC) $(CFLAG) barriere1.c -c barriere1.o 

comp: comp.o
	$(CC) $(CFLAG) comp.o $(LFLAG) -o comp.out 

comp.o:
	$(CC) $(CFLAG) comp.c -c comp.o 

clean:
	rm *.o *.out