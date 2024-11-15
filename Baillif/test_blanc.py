from Dual_Numbers_uncomplete import Dual_Numbers
from Taylor_graphs import polynome_Taylor
import matplotlib.pyplot as plt
import math

def f(x):
    if isinstance(x, Dual_Numbers):
        # Utiliser les méthodes de Dual_Numbers pour sin et exp
        return Dual_Numbers.sin(x) + (Dual_Numbers.exp(-x) / 10)
    else:
        # Utiliser les fonctions mathématiques standard pour un nombre réel
        return math.sin(x) + (math.exp(-x) / 10)

# Afficher entre -5 et 9
x = [i for i in range(-5,9)]
a = 2

# Calculer les dérivées
d_f1 = lambda x: f(Dual_Numbers(x, 1)).d
d_f2 = lambda x: d_f1(Dual_Numbers(x, 1)).d
d_f3 = lambda x: d_f2(Dual_Numbers(x, 1)).d
d_f4 = lambda x: d_f3(Dual_Numbers(x, 1)).d

derivees = []
derivees.append(f(a))
derivees.append(d_f1(a))
derivees.append(d_f2(a))
derivees.append(d_f3(a))
derivees.append(d_f4(a))

print(derivees)
y_taylor = [polynome_Taylor(derivees, a)(i) for i in x]


plt.plot(x, y_taylor, label="Taylor")
plt.xlabel("x")
plt.ylabel("y")
plt.grid(True)
plt.legend()
plt.savefig("poly")
plt.close()