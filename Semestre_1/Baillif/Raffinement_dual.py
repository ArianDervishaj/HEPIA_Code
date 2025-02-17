import numpy as np
import matplotlib.pyplot as plt
from Dual_Numbers_uncomplete import *
import matplotlib

def bissection(a, b, f):
    epsilon = 0.001
    hist = []
    if f(a).r * f(b).r >= 0:
        raise ValueError("f(a) et f(b) doivent être de signes opposés pour appliquer la méthode de bissection.")
    
    while abs((b - a).r) > epsilon:  # Use real part for comparison
        c = (a + b) / 2.0
        hist.append(c)
        if abs(f(c).r) < epsilon:  # Check if the real part of f(c) is close enough to zero
            return c, hist
        elif f(c).r * f(b).r < 0:
            a = c
        else:
            b = c
    
    return (a + b) / 2, hist

def regula_falsi(f, a, b, tol=1e-6, max_iter=100):
    if f(a).r * f(b).r >= 0:
        raise ValueError("f(a) et f(b) doivent être de signes opposés")
    
    conv_hist = []
    n_iter = 0
    
    while n_iter < max_iter:
        # Calcul du point c par la méthode de la fausse position
        pente = (f(b).r - f(a).r) / (b - a)
        c = a - f(a).r / pente
        
        fc = f(c)
        conv_hist.append(c)
        
        # Vérification du critère d'arrêt
        if abs(fc.r) < tol:
            return c, n_iter, conv_hist
        
        # Mise à jour de l'intervalle
        if f(a).r * fc.r < 0:
            b = c
        else:
            a = c
            
        n_iter += 1
    
    return c, n_iter, conv_hist

def newton(f, x0, tol=1e-6, max_iter=100):
    x = x0
    hist = [x0]
    
    for i in range(max_iter):
        fx = f(x)
        if abs(fx.r) < tol:
            return x, hist
            
        # Use the dual part of f(x + Dual_Numbers(0, 1)) to find the derivative
        dfx = f(Dual_Numbers(x.r, 1)).d
        if dfx == 0:
            raise ValueError("Dérivée nulle - La méthode de Newton ne peut pas continuer")
            
        x = x - fx.r / dfx
        hist.append(x)
        
        if len(hist) >= 2 and abs(hist[-1].r - hist[-2].r) < tol:
            return x, hist
            
    return x, hist

def secante(f, x0, x1, tol=1e-6, max_iter=100):
    hist = [x0, x1]
    
    for i in range(2, max_iter):
        f_x0 = f(x0).r
        f_x1 = f(x1).r
        
        if f_x1 - f_x0 == 0:
            raise ValueError("Division par zéro dans la méthode de la sécante.")
        
        x2 = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0)
        
        x0 = x1
        x1 = x2
        hist.append(x2)
        
        if abs(f(x2).r) < tol:
            return x2, hist
        
        if abs(x2 - x1) < tol:
            return x2, hist
    
    return x1, hist

# Function to visualize convergence
def plot_convergence(f, a, b, conv_hist, filename):
    x = np.linspace(a.r, b.r, 1000)  # Use the real parts of a and b
    y = [f(Dual_Numbers(xi)).r for xi in x]  # Evaluate f at each x as a Dual_Numbers and extract the real part
    
    plt.figure(figsize=(12, 6))
    plt.plot(x, y, 'b-', label='f(x)')
    plt.plot(x, np.zeros_like(x), 'k--', alpha=0.3)
    plt.plot([c.r for c in conv_hist], [f(c).r for c in conv_hist], 'ro-', label='Itérations')
    plt.grid(True)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Convergence de la méthode')
    plt.show()
    # plt.savefig(filename)
    # plt.close()


# Define a function that works with Dual_Numbers
f = lambda x: Dual_Numbers(x.r +3, 2 * x.r)

# Initial interval or point
a, b = Dual_Numbers(-10), Dual_Numbers(10)
x0 = Dual_Numbers(5)

# Test with different methods
print("Bissection method:")
root, hist_bissection = bissection(a, b, f)
plot_convergence(f,a,b,hist_bissection,"bis")
print(f"Root: {root}")

print("\nRegula Falsi method:")
root, _, hist_regula = regula_falsi(f, a, b)
plot_convergence(f,a,b,hist_regula,"reg")
print(f"Root: {root}")

print("\nNewton's method:")
root, hist_newton = newton(f, x0)
plot_convergence(f,a,b,hist_newton,"newton")
print(f"Root: {root}")

print("\nSecant method:")
root, hist_secant = secante(f, a, b)
plot_convergence(f,a,b,hist_secant,"sec")
print(f"Root: {root}")

