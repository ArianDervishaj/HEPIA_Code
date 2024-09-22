#include <stdbool.h>
#include <stdio.h>

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

struct replace {
  char *string;
  char new_char;
};

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

int main() {

  int ex = 2;

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
    break;
  }
  }

  return 0;
}