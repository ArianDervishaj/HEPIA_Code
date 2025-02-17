// int __sync_val_compare_and_swap(int *ptr, int oldval, int newval);
// Si val pointé == old val => return newval
#include <pthread.h>
#include <stdio.h>

#define MAX 5000

static int compter = 0;
static int lock;

// Cette fonction initialise le verrou passé en argument
void init_lock(int *lock_ptr) { *lock_ptr = 0; }

// Cette fonction verrouille (acquiert) le verrou passé en argument
void acquire_lock(int *lock_ptr) {
  while (__sync_val_compare_and_swap(lock_ptr, 0, 1))
    ;
}

// Cette fonction déverrouille (relâche) le verrou passé en argument
void release_lock(int *lock_ptr) { *lock_ptr = 0; }

void *increment() {
  for (int i = 0; i < MAX; i++) {
    acquire_lock(&lock);
    compter++;
    release_lock(&lock);
  }

  return NULL;
}

int main(int argc, char *argv[]) {

  init_lock(&lock);
  pthread_t t0, t1;
  if (pthread_create(&t0, NULL, increment, NULL) != 0) {
    printf("Erreur création t0");
  }
  if (pthread_create(&t1, NULL, increment, NULL) != 0) {
    printf("Erreur création t1");
  }

  if (pthread_join(t0, NULL) != 0) {
    printf("Erreur join t0");
  }

  if (pthread_join(t1, NULL) != 0) {
    printf("Erreur join t1");
  }

  int errors = 2 * MAX - compter;
  printf("%d errors in %d number \n", errors, MAX);
}