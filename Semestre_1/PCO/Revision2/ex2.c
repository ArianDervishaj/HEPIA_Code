// Cette fonction initialise le verrou passé en argument

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int *ptr_lock;
int compteur = 0;

void init_lock(int *lock_ptr) { *lock_ptr = 0; }
// Cette fonction verrouille (acquiert) le verrou passé en argument
void acquire_lock(int *lock_ptr) {
  while (__sync_val_compare_and_swap(lock_ptr, 0, 1)) {
  }
}
// Cette fonction déverrouille (relâche) le verrou passé en argument
void release_lock(int *lock_ptr) { *lock_ptr = 0; }

void *wait() {
  for (int i = 0; i < 50; i++) {
    acquire_lock(ptr_lock);
    compteur++;
    release_lock(ptr_lock);
  }
  return NULL;
}

int main() {
  ptr_lock = (int *)calloc(1, sizeof(int));

  pthread_t t0, t1;
  init_lock(ptr_lock);

  if (pthread_create(&t0, NULL, wait, NULL) != 0) {
    perror("Erreur création de t0");
    return EXIT_FAILURE;
  }

  if (pthread_create(&t1, NULL, wait, NULL) != 0) {
    perror("Erreur création de t1");
    return EXIT_FAILURE;
  }

  if (pthread_join(t0, NULL) != 0) {
    perror("Erreur join t0");
    return EXIT_FAILURE;
  }

  if (pthread_join(t1, NULL) != 0) {
    perror("Erreur join t1");
    return EXIT_FAILURE;
  }
  printf("Res : %d", compteur);
  return EXIT_SUCCESS;
}