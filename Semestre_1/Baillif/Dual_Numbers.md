# Dual_Numbers

Un nombre dual est de la forme :  **u = a + bε**  
où **a** est la partie réelle, et **bε** est la partie duale, avec **ε** représentant un composant infinitésimal satisfaisant **ε² = 0**.

### Instanciation des nombres duaux

Pour créer un nombre dual, utilisez :
```python
u = Dual_Numbers(real=2, dual=3)  # Représente 2 + 3ε
# ou plus simplement
u = Dual_Numbers(2, 3)
reel = u.r
duale = u.d
```

# Opérations disponibles
## Opérations de base

La classe Dual_Numbers supporte les opérations arithmétiques de base avec d'autres nombres duaux ainsi qu'avec des entiers et des flottants.

- Addition (+)
```python
    resultat = u + v
```
- Soustraction (-)
```python
    resultat = u - v
```
- Multiplication (*)
```python 
    resultat = u * v
```
- Division (/)
```python 
    resultat = u / v
```
- Négation
```python
    neg_u = -u
```

## Fonctions trigonométriques et exponentielles

La classe comprend des fonctions trigonométriques, exponentielles et logarithmiques spécifiquement adaptées aux nombres duaux.

- Cosinus
```python
    cos_u = Dual_Numbers.cos(u)
```
- Sinus
```python
    sin_u = Dual_Numbers.sin(u)
```
- Exponentielle
```python
    exp_u = Dual_Numbers.exp(u)
```
- Logarithme
```python
    log_u = Dual_Numbers.log(u)
```

# Exemples d'utilisation

```python
# Importer numpy si nécessaire
import numpy as np
import Dual_Numbers

# Créer deux nombres duaux
u = Dual_Numbers(2, 3)  # 2 + 3ε
v = Dual_Numbers(4, -1) # 4 - ε

# Opérations de base
print("u + v =", u + v)           # Addition
print("u - v =", u - v)           # Soustraction
print("u * v =", u * v)           # Multiplication
print("u / v =", u / v)           # Division

# Négation
print("-u =", -u)

# Fonctions trigonométriques et exponentielles
print("cos(u) =", Dual_Numbers.cos(u))
print("sin(u) =", Dual_Numbers.sin(u))
print("exp(u) =", Dual_Numbers.exp(u))
print("log(v) =", Dual_Numbers.log(v))

# Opérations avec des flottants et des entiers
print("u + 2.5 =", u + 2.5)       # Addition avec un flottant
print("u * 3 =", u * 3)           # Multiplication avec un entier
```