#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// A votre avis, l’implémentation de ce programme est-elle correcte ? Vérifiez votre réponse en exécutant le programme plusieurs fois.
// ◦ Si ce n’est pas le cas :
// ▪ Expliquez pourquoi le comportement est incorrect.
// Le comportement est incorrect car, 
//int code = pthread_create(&threads[i], NULL, thread, &i);
// &i aura potentiellement changer le temps que le thread soit créé ou alors il y aura des duplications de i dans les threads.
// Et on attend pas que tout les threads se finissent pour finir le programme


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
    ids[i] = i;
    int code = pthread_create(&threads[i], NULL, thread, &ids[i]);

    if (code != 0) {
      fprintf(stderr, "pthread_create failed!\n");
      return EXIT_FAILURE;
    }
  }

  for(int i = 0; i < NUM_THREADS; i++){
    if(pthread_join(threads[i],NULL) != 0){
        perror("join error");
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}