// Cette fonction initialise le verrou passé en argument

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_OF_THREADS 2
int compteur = 0;
struct barrier_t {
  int max;
  int count;
  pthread_mutex_t mutex;

} typedef barrier_t;

void barrier_init(barrier_t *b, int count) {
  b->max = count;
  pthread_mutex_init(&b->mutex, NULL);
  b->count = 0;
}

void barrier_wait(barrier_t *b) {
  pthread_mutex_lock(&b->mutex);
  b->count += 1;
  pthread_mutex_unlock(&b->mutex);
  while (b->count < b->max) {
  }
}

void barrier_detroy(barrier_t *b) {
  b->max = 0;
  b->count = 0;
  pthread_mutex_destroy(&b->mutex);
  free(b);
}

void *increment() {
  compteur++;
  return NULL;
}

int main() {
  barrier_t *barrier = calloc(1, sizeof(barrier_t));
  if (barrier == NULL) {
    perror("erreur alloc barreire");
    exit(EXIT_FAILURE);
  }
  barrier_init(barrier, NB_OF_THREADS);

  pthread_t t0, t1;

  pthread_create(&t0, NULL, increment, NULL);
  pthread_create(&t1, NULL, increment, NULL);

  barrier_wait(barrier);

  pthread_join(t0, NULL);
  pthread_join(t1, NULL);

  barrier_detroy(barrier);

  printf("%d", compteur);
  return EXIT_SUCCESS;
}