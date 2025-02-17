import numpy as np
import matplotlib.pyplot as plt
import matplotlib

def bissection(a, b, f):
    epsilon = 0.001
    hist = []
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) et f(b) doivent être de signes opposés pour appliquer la méthode de bissection.")
    
    while abs(b - a) > epsilon:
        c = (a + b) / 2.0
        hist.append(c)
        if abs(f(c)) < epsilon:  # Check if f(c) is close enough to zero
            return c, hist
        elif f(c) * f(b) < 0:
            a = c
        else:
            b = c
    
    return (a + b) / 2, hist

def regula_falsi(f, a, b, tol=1e-6, max_iter=100):
    """
    Implémentation de la méthode de la fausse position
    
    Args:
        f: fonction dont on cherche le zéro
        a, b: bornes de l'intervalle initial
        tol: tolérance pour le critère d'arrêt
        max_iter: nombre maximum d'itérations
    
    Returns:
        c: approximation de la racine
        n_iter: nombre d'itérations effectuées
        conv_hist: historique de convergence
    """
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) et f(b) doivent être de signes opposés")
    
    conv_hist = []
    n_iter = 0
    
    while n_iter < max_iter:
        # Calcul du point c par la méthode de la fausse position
        pente = (f(b) - f(a)) / (b - a)
        c = a - f(a) / pente
        
        fc = f(c)
        conv_hist.append(c)
        
        # Vérification du critère d'arrêt
        if abs(fc) < tol:
            return c, n_iter, conv_hist
        
        # Mise à jour de l'intervalle
        if f(a) * fc < 0:
            b = c
        else:
            a = c
            
        n_iter += 1
    
    return c, n_iter, conv_hist

def newton(f, df, x0, tol=1e-6, max_iter=100):
    """
    Implémentation de la méthode de Newton
    Args:
        f: fonction dont on cherche le zéro
        df: dérivée de la fonction f
        x0: point de départ
        tol: tolérance pour le critère d'arrêt
        max_iter: nombre maximum d'itérations
    Returns:
        x: approximation de la racine
        hist: historique des approximations
    """
    x = x0
    hist = [x0]
    
    for i in range(max_iter):
        fx = f(x)
        if abs(fx) < tol:
            return x, hist
            
        dfx = df(x)
        if dfx == 0:
            raise ValueError("Dérivée nulle - La méthode de Newton ne peut pas continuer")
            
        x = x - fx/dfx
        hist.append(x)
        
        if len(hist) >= 2 and abs(hist[-1] - hist[-2]) < tol:
            return x, hist
            
    return x, hist

def secante(f, x0, x1, tol=1e-6, max_iter=100):
    """
    Implémentation de la méthode de la sécante.
    
    Args:
        f: fonction dont on cherche la racine
        x0, x1: points de départ
        tol: tolérance pour le critère d'arrêt
        max_iter: nombre maximum d'itérations
    
    Returns:
        x: approximation de la racine
        hist: historique des approximations
    """
    hist = [x0, x1]
    
    for i in range(2, max_iter):
        # Calcul de la pente de la sécante
        f_x0 = f(x0)
        f_x1 = f(x1)
        
        # Calcul du nouveau point par la méthode de la sécante
        if f_x1 - f_x0 == 0:  # Eviter la division par zéro
            raise ValueError("Division par zéro dans la méthode de la sécante.")
        
        x2 = x1 - f_x1 * (x1 - x0) / (f_x1 - f_x0)
        
        # Mise à jour des points pour la prochaine itération
        x0 = x1
        x1 = x2
        hist.append(x2)
        
        # Vérification du critère d'arrêt
        if abs(f(x2)) < tol:
            return x2, hist
        
        if abs(x2 - x1) < tol:  # Si les approximations successives sont proches
            return x2, hist
    
    return x1, hist  # Retourner l'approximation finale si on atteint max_iter


# Fonction pour visualiser la convergence
def plot_convergence(f, a, b, conv_hist,filename):
    matplotlib.use("TkAgg")  # Or "Qt5Agg" if you have Qt5 installed
    x = np.linspace(a, b, 1000)
    y = f(x)
    
    plt.figure(figsize=(12, 6))
    plt.plot(x, y, 'b-', label='f(x)')
    plt.plot(x, np.zeros_like(x), 'k--', alpha=0.3)
    plt.plot(conv_hist, f(np.array(conv_hist)), 'ro-', label='Itérations')
    plt.grid(True)
    plt.legend()
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Convergence de la méthode de la fausse position')
    # plt.savefig(filename)
    # plt.close()
    plt.show()

a,b = -4, -2
f1 = lambda x: x**2 + 25
f2 = lambda x: x**3 - x**2 - 1
f3 = lambda x: x + 3

f4 = lambda x: -np.cos(3 * np.log(x * x + 1) + 1 / (x * x + 0.4))

# f_prime = lambda x: -np.cosh(x) - np.sin(x)

racine1, n_iter1, hist1 = regula_falsi(f4, a, b)
# racine1, hist1 = newton(f4,f_prime,0 )
print(f"Racine trouvée: {racine1:.8f}")
print(f"Nombre d'itérations: {len(hist1)}")
plot_convergence(f4, b, a, hist1,"fig1")

# print("Test 1: x² - 25 = 0")
# racine1, n_iter1, hist1 = regula_falsi(f3, b, a)
# print(f"Racine trouvée: {racine1:.6f}")
# print(f"Nombre d'itérations: {len(hist1)}")
# plot_convergence(f3, b, a, hist1,"fig1")


# print(f"\nTest 2: x + 3 = 0:")
# racine2, hist2 = bissection(b,a,f3)
# print(f"Racine trouvée: {racine2:.6f}")
# print(f"Nombre d'itérations: {len(hist2)}")
# plot_convergence(f3, b, a, hist2,"fig2")

# print(f"\nTest 3: x + 3 = 0:")
# df3 = lambda x: 1  # dérivée de x - 3
# racine3, hist3 = newton(f3, df3, b)  # on utilise b comme point de départ
# print(f"Racine trouvée: {racine3:.6f}")
# print(f"Nombre d'itérations: {len(hist3)}")
# plot_convergence(f3, b, a, hist3,"fig3")

# print(f"\nTest 4: x + 3 = 0:")

# racine4, hist4 = secante(f3,b,a)
# print(f"Racine trouvée: {racine4:.6f}")
# print(f"Nombre d'itérations: {len(hist4)}")
# plot_convergence(f3, b, a, hist4,"fig4")