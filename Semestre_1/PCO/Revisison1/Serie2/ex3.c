#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ThreadArgs {
  int *vals;
  int number_of_vals;
};

void *summation(void *arguments) {
  struct ThreadArgs *args = (struct ThreadArgs *)arguments;
  int *sum = calloc(1, sizeof(int));

  if (sum == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    pthread_exit(NULL); // Exit if memory allocation fails
  }

  *sum = 0;
  for (int k = 0; k < args->number_of_vals; k++) {
    *sum += args->vals[k];
  }
  return sum;
}

int main(int argc, char *argv[]) {
  int number_of_vals = argc - 1;
  int *vals = calloc(number_of_vals, sizeof(int));

  struct ThreadArgs args;
  args.vals = vals;
  args.number_of_vals = number_of_vals;

  if (vals == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < number_of_vals; i++) {
    vals[i] = atoi(argv[i + 1]);
  }

  pthread_t thread;

  int code = pthread_create(&thread, NULL, summation, &args);

  if (code != 0) {
    fprintf(stderr, "pthread_create failed\n");
    free(vals);
    return EXIT_FAILURE;
  }

  int *sum_res;
  code = pthread_join(thread, (void **)&sum_res);

  printf("Resultat est %d\n", *sum_res);
  if (code != 0) {
    fprintf(stderr, "pthread_join failed with error code %d\n", code);
    free(vals);
    return EXIT_FAILURE;
  }

  free(vals);
  free(sum_res);
  return EXIT_SUCCESS;
}