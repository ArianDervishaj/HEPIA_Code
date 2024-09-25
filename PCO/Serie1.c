#include "Serie1.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void ex1() {
  // a) les valeurs de p et pp ?
  // p = addresse de n. pp = addresse de p
  // b) la valeur de *p ?
  // 15
  // c) la valeur de *pp ?
  // l'addresse de p
  // d) la valeur de **pp ?
  // 15
  // e) Ecrivez un programme permettant de vérifier vos hypothèses

  long n = 15;
  long *p;
  long **pp;

  p = &n;
  pp = &p;

  // Printing values and addresses
  printf("La valeur de p %p\n", (void *)p);
  printf("La valeur de pp %p\n", (void *)pp);
  printf("La valeur de *p : %ld\n", *p);
  printf("La valeur de *pp : %p\n", (void *)*pp);
  printf("La valeur de **pp : %ld\n", **pp);
}

void ex2(struct replace *data) {
  // Implémentez une fonction qui remplace les espaces d'une chaîne de
  // caractères par un caractère spécifié. Votre fonction aura comme argument
  // une structure qui contiendra un pointeur sur le début d'une chaîne de
  // caractères, ainsi que le caractère de remplacement des espaces. Vous devrez
  // passer un pointeur sur la structure en argument à votre fonction. A noter
  // que votre fonction ne retournera rien. Attention : assurez-vous de passer
  // un pointeur sur un tableau de caractères non constant à votre fonction, car
  // si vous essayez d’écrire dans une chaîne de caractères littérale, votre
  // programme risque de crasher ! Par exemple écrire f("ma chaine") passe une
  // chaîne de caractères qui est constante à la fonction f()
  int i = 0;
  while (data->string[i] != '\0') {
    if (data->string[i] == ' ') {
      data->string[i] = data->new_char;
    }
    i++;
  }
}

bool test_ex2(struct replace *data) {
  int i = 0;
  while (data->string[i] != '\0') {
    if (data->string[i] == ' ') {
      return false;
    }
    i++;
  }
  return true;
}

char *ex3(struct replace *data) {
  int size = 0;
  while (data->string[size] != '\0') {
    size++;
  }

  char *new_string = (char *)calloc(size + 1, sizeof(char));
  assert((new_string != NULL) && "Erreur dans le calloc !");

  for (int i = 0; i < size; i++) {
    if (data->string[size - i - 1] == ' ') {
      new_string[i] = data->new_char;
    } else {
      new_string[i] = data->string[size - i - 1];
    }
  }
  new_string[size] = '\0';
  return new_string;
}

bool test_ex3(struct replace *data, struct replace *old_data) {
  int size = 0;
  while (old_data->string[size] != '\0') {
    size++;
  }

  for (int i = 0; i < size; i++) {

    if (old_data->string[i] == ' ') {
      if (data->string[i] != data->new_char) {
        return false;
      }
    } else {
      if (data->string[i] != old_data->string[i]) {
        return false;
      }
    }
  }

  return true;
}

void ex4(int n, float x, int y) {
  for (int m = 0; m < n; m++) {
    float result = pow(x, (y + m));
    printf("Iteration %d: Result = %f\n", m, result);
  }
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int ex = 4;

  if (ex == 4 && argc != 4) {
    printf("Bouffon ! Tu sais pas compter jusqu'à 4 !\n");
    printf("Usage: %s <n (iterations)> <x (float)> <y (int)>\n", argv[0]);
    return 1;
  }

  switch (ex) {
  case 1: {
    ex1();
    break;
  }
  case 2: {
    char string[] = "Ceci est un test !";
    struct replace data = {string, '*'};

    ex2(&data);
    printf("Modified string: %s\n", data.string);
    printf("%d \n", test_ex2(&data));

    break;
  }
  case 3: {
    char string[] = "Ceci est un test !";
    struct replace data = {string, '*'};
    char *test = ex3(&data);

    struct replace new_data = {test, '*'};

    printf("%s\n", test);
    printf("%s \n", data.string);

    printf("%d \n", test_ex3(&new_data, &data));
    free(test);
    break;
  }
  case 4: {

    int n = atoi(argv[1]);
    float x = atof(argv[2]);
    int y = atoi(argv[3]);

    ex4(n, x, y);
    break;
  }
  }

  return 0;
}
