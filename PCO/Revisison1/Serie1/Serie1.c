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
  // Implémentez une fonction similaire à celle de l'exercice précédent,
  // mais qui va en plus inverser la chaîne de caractères.
  // Cette fois-ci, on ne désire pas modifier la chaîne de caractères passée
  // en argument, mais renvoyer une nouvelle chaîne, inversée avec les espaces
  // remplacés par le caractère spécifié. La nouvelle chaîne renvoyée sera
  // allouée avec la fonction malloc.

  int size = 0;
  while (data->string[size] != '\0') {
    size++;
  }

  char *new_string = (char *)calloc(size + 1, sizeof(char)); // + 1 pour le \0
  int i = 0;

  while (data->string[i] != '\0') {
    if (data->string[size - i - 1] == ' ') {
      new_string[i] = data->new_char;
    } else {
      new_string[i] = data->string[size - i - 1];
    }
    i++;
  }
  new_string[size + 1] = '\0';
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

void ex4(char *label, int n, float x, int y) {
  printf("%s\n", label);
  for (int i = 0; i < n; i++) {
    float res = pow(x, y + i);
    printf("%f^%d = %f \n", x, y + i, res);
  }
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  int ex = 4;

  if (ex == 4 && argc != 5) {
    printf("Bouffon ! Tu sais pas compter jusqu'à 4 !\n");
    printf("Usage: %s label: <n (iterations)> <x (float)> <y (int)>\n",
           argv[0]);
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

    printf("%s\n", test);
    printf("%s \n", data.string);
    free(test);
    break;
  }
  case 4: {
    char *label = argv[1];
    int n = atoi(argv[2]);
    float x = atof(argv[3]);
    int y = atoi(argv[4]);

    ex4(label, n, x, y);
    break;
  }
  }

  return 0;
}
