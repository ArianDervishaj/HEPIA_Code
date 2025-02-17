#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// For detailed info about memory barriers and instruction reordering:
// https://en.wikipedia.org/wiki/Memory_barrier

#define COUNT  5000000

static int n = 0;

static volatile bool intention[2] = { false, false };
static volatile int turn = 0;

static void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
 * Argument is the thread id (0 or 1) as an int.
 */
static void *peterson(void *arg) {
	int *thread_id = (int *) arg;
	int id = *thread_id;

	int i;
	for (i = 0; i < COUNT; i++) {
		intention[id] = true;
		turn = 1-id;
#ifdef USE_MEMORY_BARRIER
		// Full memory barrier
		__sync_synchronize();
#endif
		while (intention[1-id] && turn == 1-id);
		// critical section
		n++;
		// end of critical section
		intention[id] = false;
	}

	return NULL;
}

int main() {
	pthread_t thread1, thread2;
	int id1 = 0, id2 = 1;

	if (pthread_create(&thread1, NULL, peterson, &id1) != 0)
		error("pthread_create");
	if (pthread_create(&thread2, NULL, peterson, &id2) != 0)
		error("pthread_create");

	if (pthread_join(thread1, NULL) != 0)
		error("pthread_join");
	if (pthread_join(thread2, NULL) != 0)
		error("pthread_join");

	int errors = 2*COUNT-n;
	if (errors)
		printf("%d ERRORS out of %d concurrent iterations!\n", errors, COUNT);
	else
		printf("OK: 0 errors in %d concurrent iterations\n", COUNT);

	return EXIT_SUCCESS;
}
