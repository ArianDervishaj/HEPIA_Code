#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sum = 0;
int *vals;
int number_of_vals;

void *summation() {
  for (int k = 0; k < number_of_vals; k++) {
    sum += vals[k];
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  number_of_vals = argc - 1;
  vals = calloc(number_of_vals, sizeof(int));
  if (vals == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < number_of_vals; i++) {
    vals[i] = atoi(argv[i + 1]);
  }

  pthread_t thread;

  int code = pthread_create(&thread, NULL, summation, NULL);

  if (code != 0) {
    fprintf(stderr, "pthread_create failed\n");
    free(vals);
    return EXIT_FAILURE;
  }

  code = pthread_join(thread, NULL);

  printf("Resultat est %d\n", sum);
  if (code != 0) {
    fprintf(stderr, "pthread_join failed with error code %d\n", code);
    free(vals);
    return EXIT_FAILURE;
  }

  free(vals);
  return EXIT_SUCCESS;
}