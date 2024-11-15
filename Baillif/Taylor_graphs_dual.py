import Dual_Numbers_uncomplete as Dn
import math
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

# Function to calculate the Taylor series using dual numbers
def polynome_Taylor(f, a, n):
    def T(x):
        res = 0
        for k in range(n + 1):
            # Calculate the k-th derivative at `a` using dual numbers
            if k == 0:
                derivative_at_a = f(Dn.Dual_Numbers(a, 0)).r
            else:
                dual_number = Dn.Dual_Numbers(a, 1)
                for _ in range(k - 1):
                    dual_number = Dn.Dual_Numbers(dual_number.r, 1)
                derivative_at_a = f(dual_number).d

            # Add term to Taylor series
            term = derivative_at_a / math.factorial(k) * (x - a) ** k
            res += term

        return res
    return T


# Define the function with a docstring to automatically extract its label
def f(x):
    """-sinh(x) + cos(x)"""
    return -Dn.Dual_Numbers.sinh(x) + Dn.Dual_Numbers.cos(x)

def main():
    a = -np.pi
    n = 4
    borne_inf = -3
    borne_sup = 3
    x_values = [i for i in range(borne_inf, borne_sup+1)]
    y_values = [(-np.sin(i) + np.cos(i)) for i in x_values]

    # Get the Taylor polynomial
    taylor = polynome_Taylor(f, a, n)
    y_taylor = [taylor(i) for i in x_values]

    # Get function description from docstring for automatic labeling
    function_label = f.__doc__ or "Function"

    # Plotting
    plt.plot(x_values, y_values, label=f"Vraie fonction: {function_label}")
    plt.plot(x_values, y_taylor, label=f"Taylor de {function_label} en {a}")

    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.grid(True)
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    matplotlib.use("TkAgg")  # Or "Qt5Agg" if you have Qt5 installed
    main()
