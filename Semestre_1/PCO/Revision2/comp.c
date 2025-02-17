#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 100

double x(int k, int i) { return A * sin(k + i); }

double seq(int I, int M) {
  double r = 0;
  int k = I - 1;

  for (int i = 0; i < M; i++) {
    if (sin(i + k) > 0) {
      r += x(k, i);
    }
  }

  return r;
}

void *conc(void *args) {
  int *threads_arg = (int *)args;
  int id = *threads_arg;

  printf("id : %d \n", id);

  return NULL;
}
int res = 0;

void *sum(void *args) {
  int *threads_arg = (int *)args;
  int id = *threads_arg;

  printf("c bon\n");
  return NULL;
}

int main(int argc, char *argv[]) {

  if (argc < 4) {
    printf("Usage: %s <M> <I>\n", argv[0]);
    return 1;
  }

  int M = atoi(argv[1]);
  int N = atoi(argv[2]);
  int I = atoi(argv[3]);

  pthread_t threads[N];
  for (int b = 0; b < N; b++) {
    int *id = (int *)malloc(sizeof(int *));
    *id = b;
    int err;

    if (b == 0) {
      err = pthread_create(&threads[b], NULL, sum, id);
    } else {
      err = pthread_create(&threads[b], NULL, conc, id);
    }


    if (err) {
      perror("Erreur création thread");
    }
  }

  for (int x = 1; x <= I; x++) {
    double r = seq(x, M);
    printf("Itérations %d : %lf \n", x, r);
  }

  return 0;
}