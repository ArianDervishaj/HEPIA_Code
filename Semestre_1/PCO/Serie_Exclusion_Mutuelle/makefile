CC=gcc -Wall -Wextra -std=gnu11
LIBS=-lpthread -lrt
OUT=lock peterson_with_barrier peterson_without_barrier 
#peterson_with_barrier.s peterson_without_barrier.s

all: $(OUT)

lock: lock.c
	$(CC) $< -o $@ $(LIBS)

peterson_with_barrier: peterson.c
	$(CC) -DUSE_MEMORY_BARRIER $< -o $@ $(LIBS)

peterson_without_barrier: peterson.c
	$(CC) $< -o $@ $(LIBS)

#peterson_with_barrier.s: peterson.c
#	$(CC) -DUSE_MEMORY_BARRIER $< -S -o $@

#peterson_without_barrier.s: peterson.c
#	$(CC) $< -S -o $@

clean:
	rm -f $(OUT)
