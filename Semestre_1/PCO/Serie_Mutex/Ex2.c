#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

typedef struct barrier {
  int count;         // Nombre de threads nécessaires pour passer la barrière
  int current_count; // Nombre de threads actuellement à la barrière
  pthread_mutex_t mutex; // Mutex pour protéger l'accès à la barrière
  pthread_cond_t cond;   // Condition variable pour signaler les threads
} barrier_t;

typedef struct {
  int thread_id;      // Thread ID
  barrier_t *barrier; // Pointer to the barrier
} thread_arg_t;

// • Une fonction d’initialisation d’un objet barrière :
void barrier_init(barrier_t *b, int count) {
  b->count = count;
  b->current_count = 0;
  pthread_mutex_init(&b->mutex, NULL);
  pthread_cond_init(&b->cond, NULL);
}

void barrier_wait(barrier_t *b) {
  pthread_mutex_lock(&b->mutex);

  b->current_count++;

  if (b->current_count == b->count) {
    pthread_cond_broadcast(&b->cond); // Réveiller tous les threads en attente
    b->current_count = 0; // Réinitialiser pour la prochaine utilisation
  } else {
    // Attendre que tous les threads atteignent la barrière
    pthread_cond_wait(&b->cond, &b->mutex);
  }

  pthread_mutex_unlock(&b->mutex); // Libérer le mutex
}

// Fonction de destruction de la barrière
void barrier_destroy(barrier_t *b) {
  pthread_mutex_destroy(&b->mutex);
  pthread_cond_destroy(&b->cond);
}

// Function executed by each thread
void *thread_function(void *arg) {
  thread_arg_t *targ = (thread_arg_t *)arg;
  int thread_id = targ->thread_id;
  barrier_t *barrier = targ->barrier;

  printf("Thread %d atteint la barrière.\n", thread_id);
  barrier_wait(barrier); // Wait at the barrier
  printf("Thread %d passe la barrière.\n", thread_id);

  return NULL;
}

int main() {
  barrier_t barrier;
  barrier_init(&barrier, NUM_THREADS);

  pthread_t threads[NUM_THREADS];
  thread_arg_t thread_args[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_args[i].thread_id = i;      // Assign thread ID
    thread_args[i].barrier = &barrier; // Pass the barrier
    if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) !=
        0) {
      perror("pthread_create failed");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  barrier_destroy(&barrier);

  printf("All threads have completed.\n");
  return 0;
}