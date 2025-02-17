import numpy as np
import math
import matplotlib.pyplot as plt
from math import factorial
from typing import Callable, List
from Dual_Numbers_complete import *

############################################################################################################
# GRADIENTS
############################################################################################################

def gradient_at_point(f: Callable, P: List[float]) -> np.ndarray:
    """
    Calcule le gradient d'une fonction F: R^n -> R en un point P
    
    Args:
        f: La fonction dont on veut calculer le gradient
        P: Le point où calculer le gradient (liste des coordonnées)
    
    Returns:
        np.ndarray: Le gradient de f au point P
    """
    n = len(P)  # dimension de l'espace
    grad = np.zeros(n)
    
    for i in range(n):
        # On crée un point dual où seule la i-ème composante a une partie duale = 1
        P_dual = [Dual_Number(P[j], 1 if j == i else 0) for j in range(n)]
        
        # On évalue f au point dual
        result = f(P_dual)
        
        # La partie duale du résultat est la dérivée partielle par rapport à la i-ème variable
        if isinstance(result, Dual_Number):
            grad[i] = result.d
        else:
            grad[i] = 0  # Si le résultat n'est pas dual, la dérivée est 0
            
    return grad

def test_gradients():
    # Fonction 1: F(x, y) = 3x²y + 2xy² - xy + 2x - 1
    def F1(P):
        x, y = P[0], P[1]
        return 3*x**2*y + 2*x*y**2 - x*y + 2*x - 1
    
    P1 = [1, 1]
    grad1 = gradient_at_point(F1, P1)
    print("\nFonction 1: F(x, y) = 3x²y + 2xy² - xy + 2x - 1")
    print(f"∇F1(1,1) = {grad1}")
    # Résultat attendu: [3*2*1 + 2*1² - 1 + 2, 3*1² + 2*1*2*1 - 1] = [7, 5]
    
    # Fonction 2: F(x, y, z) = x·y·z + x² + y²
    def F2(P):
        x, y, z = P[0], P[1], P[2]
        return x*y*z + x**2 + y**2
    
    P2 = [0, 1, -1]
    grad2 = gradient_at_point(F2, P2)
    print("\nFonction 2: F(x, y, z) = x·y·z + x² + y²")
    print(f"∇F2(0,1,-1) = {grad2}")
    # Résultat attendu: [y*z + 2x, x*z + 2y, x*y]|_{(0,1,-1)} = [-1, 2, 0]
    
    # Fonction 3: F(x, y, z) = x·e^(y²+z²)
    def F3(P):
        x, y, z = P[0], P[1], P[2]
        return x * Dual_Number.exp(y**2 + z**2)
    
    P3 = [1, 1, 1]
    grad3 = gradient_at_point(F3, P3)
    print("\nFonction 3: F(x, y, z) = x·e^(y+z)")
    print(f"∇F3(1,1,1) = {grad3}")
    # Résultat attendu: [e^(y+z), x·e^(y+z), x·e^(y+z)]|_{(1,1,1)} = [e², e², e²]
    
    # Fonction 4: F(x, y) = sin(x)cos(y) + sin(y)cos(x)
    def F4(P):
        x, y = P[0], P[1]
        return (Dual_Number.sin(x) * Dual_Number.cos(y) + 
                Dual_Number.sin(y) * Dual_Number.cos(x))
    
    P4 = [np.pi/4, np.pi/4]
    grad4 = gradient_at_point(F4, P4)
    print("\nFonction 4: F(x, y) = sin(x)cos(y) + sin(y)cos(x)")
    print(f"∇F4(π/4,π/4) = {grad4}")
    # Résultat attendu: [cos(x)cos(y) - sin(y)sin(x)]|_{(π/4,π/4)} = [0, 0]

if __name__ == "__main__":
    test_gradients()