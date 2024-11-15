# 1. Méthode de la Bissection (bissection)

## Entrée :

- **a (float)** : borne inférieure de l'intervalle initial.
- **b (float)** : borne supérieure de l'intervalle initial.
- **f (fonction)** : fonction pour laquelle on cherche la racine. Elle doit être continue dans l'intervalle et changer de signe entre a et b.

## Retour :

- **racine (float)** : approximation de la racine trouvée par la méthode.
- **historique (list)** : liste des valeurs successives de la racine approximée au fil des itérations.

## **Explication :** 
La méthode de la bissection divise l'intervalle en deux à chaque itération, en choisissant le sous-intervalle où la fonction change de signe. Elle converge toujours vers une racine si la fonction est continue et que les bornes initiales encadrent une racine.

# 2. Méthode de Newton (newton)

## Entrée :

- **f (fonction)** : fonction pour laquelle on cherche la racine.
- **df (fonction)** : dérivée de la fonction f.
- **x0 (float)** : point de départ pour l'itération.
- **tol (float, optionnel)** : tolérance pour le critère d'arrêt (par défaut 1e-6).
- **max_iter (int, optionnel)** : nombre maximum d'itérations (par défaut 100).

## Retour :
- **racine (float)** : approximation de la racine trouvée par la méthode.- **historique (list)** : liste des valeurs successives de la racine approximée au fil des itérations.

## Explication :
La méthode de Newton utilise la dérivée de la fonction pour calculer la racine à chaque itération via une mise à jour de l'approximation selon la formule xn+1=xn−f(xn)f′(xn)xn+1​=xn​−f′(xn​)f(xn​)​. Elle converge rapidement si l'initialisation est proche de la racine, mais peut diverger si la dérivée est nulle ou si les points initiaux sont mal choisis.

# 3. Méthode de la Sécante (secante)

## Entrée :

- **f (fonction)** : fonction pour laquelle on cherche la racine.
- **x0 (float)** : premier point de départ.
- **x1 (float)** : deuxième point de départ.
- **tol (float, optionnel)** : tolérance pour le critère d'arrêt (par défaut 1e-6).
- **max_iter (int, optionnel)** : nombre maximum d'itérations (par défaut 100).

## Retour :

- **racine (float)** : approximation de la racine trouvée par la méthode.
- **historique (list)** : liste des valeurs successives de la racine approximée au fil des itérations.

## Explication :
La méthode de la sécante utilise deux points initiaux et calcule la racine en utilisant la pente de la droite reliant ces deux points. Elle ne nécessite pas la dérivée de la fonction, mais elle peut échouer à converger si les points initiaux sont mal choisis.

# 4. Méthode de la Fausse Position (regula_falsi)

## Entrée :

- **f (fonction)** : fonction pour laquelle on cherche la racine.
- **a (float**) : borne inférieure de l'intervalle initial.
- **b (float**) : borne supérieure de l'intervalle initial.
- **tol (float, optionnel**) : tolérance pour le critère d'arrêt (par défaut 1e-6).
- **max_iter (int, optionnel**) : nombre maximum d'itérations (par défaut 100).

## Retour :

- **racine (float)** : approximation de la racine trouvée par la méthode.
- **n_iter (int)** : nombre d'itérations effectuées.
- **historique (list)** : liste des valeurs successives de la racine approximée au fil des itérations.

## Explication :
La méthode de la fausse position est similaire à la bissection, mais au lieu de prendre le milieu de l'intervalle, elle utilise un point c où la droite passant par (a, f(a)) et (b, f(b)) coupe l'axe des abscisses. Elle est plus rapide que la bissection mais ne garantit pas toujours la convergence.