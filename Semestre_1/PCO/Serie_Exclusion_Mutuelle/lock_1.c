#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define COUNT  5000000 


static int n = 0;
static int lock;

/**
 * Initialize a lock.
 * @param lock the lock to initialize.
 */
static void init_lock(int *lock_ptr) {
	*lock_ptr = 0;
}

/**
 * Acquire a lock.
 * @param lock the lock to acquire.
 */
static void acquire_lock(int *lock_ptr) {
	while (__sync_val_compare_and_swap(lock_ptr, 0, 1));
}

/**
 * Release a lock.
 * @param lock the lock to release.
 */
static void release_lock(int *lock_ptr) {
	*lock_ptr = 0;
}

/**
 * Thread function increasing a shared variable.
 * @param arg unused argument
 * @return nothing
 */
static void *compute(__attribute__((unused)) void *arg) {
	int i;
	for (i = 0; i < COUNT; i++) {
		// start of critical section
		acquire_lock(&lock);
		n++;
		release_lock(&lock);
		// end of critical section
	}

	return NULL;
}

/**
 * Print an error message and exit the process with an error code.
 * @param msg the message to print.
 */
static void error(char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
 * Program's entry point.
 * @return status code.
 */
int main() {
	pthread_t thread1, thread2;

	init_lock(&lock);

	if (pthread_create(&thread1, NULL, compute, NULL) != 0)
		error("pthread_create");
	if (pthread_create(&thread2, NULL, compute, NULL) != 0)
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
