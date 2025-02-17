#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadArgs {
  int nb_numbers;
  int *numbers;
} ThreadArgs_t;

void *summation(void *arg) {
  ThreadArgs_t *args = (ThreadArgs_t *)arg;
  int *sum = (int *)calloc(1, sizeof(int));

  *sum = 0;
  for (int i = 0; i < args->nb_numbers; i++) {
    *sum += args->numbers[i];
  }

  return sum; // Return sum directly, not &sum
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s NUM1 NUM2...\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Allocate memory for args and numbers
  ThreadArgs_t *args = (ThreadArgs_t *)malloc(sizeof(ThreadArgs_t));
  args->nb_numbers = argc - 1;
  args->numbers = (int *)malloc(args->nb_numbers * sizeof(int));

  for (int i = 0; i < args->nb_numbers; i++) {
    args->numbers[i] = atoi(argv[i + 1]);
  }

  pthread_t t;
  int code = pthread_create(&t, NULL, summation, args);
  if (code != 0) {
    fprintf(stderr, "ERROR: pthread_create failed\n");
    free(args->numbers);
    free(args);
    return EXIT_FAILURE;
  }

  int *sum;
  pthread_join(t, (void **)&sum);

  printf("TOTAL = %d\n", *sum);

  // Free allocated memory
  free(sum);
  free(args->numbers);
  free(args);

  return EXIT_SUCCESS;
}
