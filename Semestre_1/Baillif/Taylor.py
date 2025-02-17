import math
import matplotlib.pyplot as plt
import numpy as np

# Define the function and its derivatives
def f(x):
    """-sinh(x) + cos(x)"""
    return -np.sinh(x) + np.cos(x)

def f_prime(x):
    """-cosh(x) - sin(x)"""
    return -np.cosh(x) - np.sin(x)

def f_double_prime(x):
    """-sinh(x) - cos(x)"""
    return -np.sinh(x) - np.cos(x)

def f_triple_prime(x):
    """-cosh(x) + sin(x)"""
    return -np.cosh(x) + np.sin(x)

def f_quadruple_prime(x):
    """-sinh(x) + cos(x)"""
    return -np.sinh(x) + np.cos(x)

# Function to calculate the Taylor polynomial
def polynome_Taylor(a, n):
    # Define the Taylor series terms manually based on the derivatives
    derivatives = [f(a), f_prime(a), f_double_prime(a), f_triple_prime(a), f_quadruple_prime(a)]
    
    def T(x):
        res = 0
        for k in range(n + 1):
            term = derivatives[k] / math.factorial(k) * (x - a) ** k
            res += term
        return res
    
    return T

def main():
    a = -np.pi/4
    n = 4
    borne_inf = -3
    borne_sup = 3
    x_values = np.linspace(borne_inf, borne_sup, 100)
    y_values = [f(x) for x in x_values]

    # Get the Taylor polynomial
    taylor = polynome_Taylor(a, n)
    y_taylor = [taylor(x) for x in x_values]

    # Get function description from docstring for automatic labeling
    function_label = f.__doc__ or "Function"

    # Plotting
    plt.plot(x_values, y_values, label=f"Vraie fonction: {function_label}")
    plt.plot(x_values, y_taylor, label=f"Taylor de {function_label} en -pi/4")

    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.grid(True)
    plt.legend()

    # Set y-axis limits

    plt.savefig("Exo3_Dervishaj_Arian")
    plt.close()

if __name__ == "__main__":
    main()
