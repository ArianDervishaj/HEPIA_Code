#include "thread_wrapper.h"
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG

#define STACK_SIZE 100000
#define THREAD_COUNT 100
#define NB_OF_PUSH_POP 1000

// Barrier used to make sure all threads are created and ready before starting
// to run the stack test
pthread_barrier_t *b;

typedef struct {
  int max_size;
  int current_size;
  int *stack;
  pthread_mutex_t mutex;
} stack_t;

typedef struct {
  int id;
  stack_t *stack;
} thr_params;

bool stack_create(stack_t *s, int max_size) {
  if (s == NULL) {
    return false;
  }
  pthread_mutex_init(&s->mutex, NULL);
  s->current_size = 0;
  s->max_size = max_size;
  s->stack = (int *)calloc(s->max_size, sizeof(int));
  if (s->stack == NULL) {
    return false;
  }
  return true;
}

void stack_destroy(stack_t *s) {
  pthread_mutex_lock(&s->mutex);
  s->current_size = 0;
  s->max_size = 0;
  if (s->stack != NULL) {
    free(s->stack);
  }
  pthread_mutex_unlock(&s->mutex);
  pthread_mutex_destroy(&s->mutex);
}

void stack_push(stack_t *s, int val) {
  pthread_mutex_lock(&s->mutex);
  if (s->current_size >= s->max_size) {
    printf("Stack overflow, Cannot push %d in the stack.\n", val);
    pthread_mutex_unlock(&s->mutex);
    return;
  }

  s->stack[s->current_size++] = val;
  pthread_mutex_unlock(&s->mutex);
}

int stack_pop(stack_t *s) {
  pthread_mutex_lock(&s->mutex);
  if (s->current_size <= 0) {
    printf("Stack underflow, nothing to pop\n");
    pthread_mutex_unlock(&s->mutex);
    return INT32_MIN;
  }

  int return_val = s->stack[--s->current_size];
  pthread_mutex_unlock(&s->mutex);
  return return_val;
}

bool stack_is_empty(stack_t *s) {
  pthread_mutex_lock(&s->mutex);
  bool result = (s->current_size == 0);
  pthread_mutex_unlock(&s->mutex);
  return result;
}

void *test_stack(void *data) {
  bar_wait(b);

  thr_params *p = (thr_params *)data;

  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  unsigned int seed = (unsigned int)ts.tv_nsec;

  for (int i = 0; i < NB_OF_PUSH_POP; i++) {
    // push
    int val = rand_r(&seed) % 1000;
    stack_push(p->stack, val);

    // pop
    if (!stack_is_empty(p->stack)) {
      stack_pop(p->stack);
    }
  }
  return NULL;
}

int main() {
  b = bar_create(THREAD_COUNT);

  stack_t s;
  if (!stack_create(&s, STACK_SIZE)) {
    fprintf(stderr, "Failed creating stack!\n");
    return EXIT_FAILURE;
  }
#ifdef DEBUG
  printf("Created stack of %d\n", STACK_SIZE);
#endif

#ifdef DEBUG
  printf("Launching %d threads\n", THREAD_COUNT);
#endif
  pthread_t t[THREAD_COUNT];
  thr_params p[THREAD_COUNT];
  for (int i = 0; i < THREAD_COUNT; i++) {
    p[i].id = i;
    p[i].stack = &s;
    thread_create(&t[i], test_stack, &p[i]);
  }

  for (int i = 0; i < THREAD_COUNT; i++)
    thread_join(t[i], NULL);

#ifdef DEBUG
  printf("Stack empty ? %s\n", stack_is_empty(&s) ? "yes" : "NO!");
#endif

  stack_destroy(&s);
#ifdef DEBUG
  printf("Stack destroyed\n");
#endif

  bar_destroy(b);

  return EXIT_SUCCESS;
}
