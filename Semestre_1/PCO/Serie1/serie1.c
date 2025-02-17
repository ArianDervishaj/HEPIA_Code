#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 16

void *thread(void *thread_id) {
  int id = *((int *)thread_id);
  printf("Hello from thread %d\n", id);
  return NULL;
}
int main() {
  pthread_t threads[NUM_THREADS];
  int ids[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    int *id = malloc(sizeof(int));
    if (id == NULL) {
      fprintf(stderr, "ERROR ID MALLOC");
      return EXIT_FAILURE;
    }
    *id = i;
    int code = pthread_create(&threads[i], NULL, thread, id);
    if (code != 0) {
      fprintf(stderr, "pthread_create failed!\n");
      return EXIT_FAILURE;
    }

  }
  return EXIT_SUCCESS;
}