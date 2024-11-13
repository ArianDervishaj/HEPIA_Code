
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *numbers;
int nb_numbers;
int sum_tot = 0;
void *summation(void *arg) {
  for (int i = 0; i < nb_numbers; i++) {
    sum_tot += numbers[i];
  }
  return NULL;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage %s NUM 1 NUM 2... \n", argv[0]);
    return EXIT_FAILURE;
  }
  nb_numbers = argc - 1;
  numbers = (int *)calloc(nb_numbers, sizeof(int));

  for (int i = 0; i < nb_numbers; i++) {
    numbers[i] = atoi(argv[i + 1]);
  }
  pthread_t t;
  int code = pthread_create(&t, NULL, summation, NULL);
  if (code != 0) {
    fprintf(stderr, "ERROR");
    return EXIT_FAILURE;
  }
  pthread_join(t, NULL);
  printf("TOTAL = %d", sum_tot);
  free(numbers);
  return EXIT_SUCCESS;
}