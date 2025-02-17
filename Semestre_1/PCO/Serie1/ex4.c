#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Args {
  int M;
  int N;
  int start_index;
} Args_t;

void *sum(void *args) {
  Args_t *params = (Args_t *)args;
  int *partial = calloc(1, sizeof(int));
  for (int j = params->start_index; j <= params->N; j += params->M) {
    *partial += j;
  }
  free(params);
  return partial;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage : %s N M", argv[0]);
    return EXIT_FAILURE;
  }
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);

  pthread_t threads[M];
  int total_sum = 0;

  for (int i = 0; i < M; i++) {
    Args_t *param = (Args_t *)calloc(1, sizeof(Args_t));
    param->M = M;
    param->N = N;
    param->start_index = i+1;

    int code = pthread_create(&threads[i], NULL, sum, param);
    if (code != 0) {
      fprintf(stderr, "Error pthread_create");
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < M; i++) {
    int *partial;
    int code = pthread_join(threads[i], (void **)&partial);
    if (code != 0) {
      fprintf(stderr, "Error pthread_create");
    }
    total_sum += *partial;
    free(partial);
  }

  printf("total_sum = %d", total_sum);
  return EXIT_SUCCESS;
}