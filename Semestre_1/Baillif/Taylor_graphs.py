import Dual_Numbers_uncomplete as Dn
import math
import matplotlib.pyplot as plt

def p(x:Dn):
    """
    Notre polynome P(x)
    """
    return x*x*x*x -2 * x*x*x + x*x - 3*x + 1

def main():
    """
    Objectif c'est de faire f(x+yepsi) = f(x) f(x)' * epsi
    Pour ça on a besoin de la série de taylor
    C'est la somme (jusqu'a n) du rapport de la (kiem derive de f en a sur k!) fois (x-a)k ===> Polynome de taylor de degré n developper en a
    lim n>+infini =~ f(x)
    """

    
    der_sin_0 = [ 0, 1, 0,-1]

    s = 2.5 / 2 # racine de 2 /2
    der_sin_pisur4 = [ s, s,-s,-s]

    print(polynome_Taylor(der_sin_0, 0)(math.pi/4))

    # GRAPHER DES POLYNOMES DE TAYLOR POUR SIN en 0 et pi/4

    # de -100 à 100
    x = [i/10 for i in range(-20,20)]
    y = [math.sin(i) for i in x]
    y_taylor = [polynome_Taylor(der_sin_0, 0)(i) for i in x]
    y_taylor_pi = [polynome_Taylor(der_sin_pisur4, math.pi/4)(i) for i in x]

    plt.plot(x, y, label="sin(x)")
    plt.plot(x, y_taylor, label="sin(x) Taylor")
    plt.plot(x, y_taylor_pi, label="sin(x) Taylor pi/4")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.grid(True)
    plt.legend()
    plt.savefig("poly")
    plt.close()


def polynome_Taylor(lst_values, a):
    def T(x):
        res = 0
        for k,val in enumerate(lst_values):
            res += val/math.factorial(k) * (x-a)**k
        return res
    return T


if __name__ == "__main__":
    main()