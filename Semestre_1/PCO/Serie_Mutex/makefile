CC=gcc -Wall -Wextra -std=gnu99 -g
LIBS=-lpthread -lm -lrt
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
BINS=$(SRCS:%.c=%)

all: Ex3_etu


Ex3_etu:   Ex3_etu.o thread_wrapper.o 
	$(CC) $^ -o $@ $(LIBS)

Ex3_etu.o: Ex3_etu.c  thread_wrapper.h
	$(CC) $< -c


thread_wrapper.o: thread_wrapper.c thread_wrapper.h
	$(CC) $< -c

clean:
	rm -f $(BINS) $(OBJS)
