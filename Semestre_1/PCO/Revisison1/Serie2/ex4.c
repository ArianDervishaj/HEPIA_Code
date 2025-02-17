// Nous souhaitons écrire un programme calculant la somme des entiers de 1 à N à
// l’aide de M threads. Chaque thread calculera la somme d’un sous-ensemble de
// ces entiers et la somme globale sera obtenue en calculant la somme des
// résultats intermédiaires de chaque thread. Les entiers sont répartis
// uniformément entre les threads comme suit (exemple avec 3 threads) :
// • Thread 1 : 1, 4, 7, . . .
// • Thread 2 : 2, 5, 8, . . .
// • Thread 3 : 3, 6, 9, . . .
// Le programme doit lancer M threads, attendre qu’ils se terminent, faire la
// somme des résultats intermédiaires et afficher le résultat. Les valeurs N et
// M seront passées en ligne de commande. Il est important que le programme
// respecte les points suivants : • L’implémentation ne doit utiliser aucune
// variable globale. • Le travail à effectuer pour chaque thread créé doit être
// aussi équitable que possible, quel que soit les valeurs N et M choisies par
// l’utilisateur (ex : N = 20, M = 8). • Réaliser un test de validation
// automatiquement du résultat obtenu avec une version séquentielle de
// l’algorithm
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ThreadArgs {
  int N;
  int M;
  int start_index;

} ThreadArgs_t;

void *sum(void *arguments) {
  ThreadArgs_t *args = (ThreadArgs_t *)arguments;
  int *res = calloc(1, sizeof(int));
  if (res == NULL) {
    fprintf(stderr, "Error une the allocation of res ");
    return NULL;
  }

  *res = 0;
  for (int i = args->start_index; i <= args->N; i += args->M) {
    *res += i;
  }

  free(args);

  return res;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./%s <N> <M>", argv[0]);
    return EXIT_FAILURE;
  }
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);

  pthread_t *threads = (pthread_t *)calloc(M, sizeof(pthread_t));

  if (threads == NULL) {
    fprintf(stderr, "Error une the allocation of threads ");
  }

  int total_sum = 0;

  for (int i = 0; i < M; i++) {
    ThreadArgs_t *thread_args = calloc(1, sizeof(ThreadArgs_t));
    thread_args->N = N;
    thread_args->M = M;
    thread_args->start_index = i + 1;

    int code = pthread_create(&threads[i], NULL, sum, thread_args);

    if (code != 0) {
      fprintf(stderr, "Error in the creation of threads");
      free(threads);
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < M; i++) {

    int *intermediate_sum;
    int code = pthread_join(threads[i], (void **)&intermediate_sum);

    if (code != 0) {
      fprintf(stderr, "Error in the join of the threads");
      free(intermediate_sum);
      free(threads);
      return EXIT_FAILURE;
    }
    printf("Thread %d : %d\n", i + 1, *intermediate_sum);
    total_sum += *intermediate_sum;
    free(intermediate_sum);
  }

  printf("Total sum = %d \n", total_sum);
  free(threads);

  return EXIT_SUCCESS;
}