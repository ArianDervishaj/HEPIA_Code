def bissection(a, b, f):
    epsilon = 0.001
    
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) et f(b) doivent être de signes opposés pour appliquer la méthode de bissection.")
    
    while abs(b - a) > epsilon:
        c = (a + b) / 2.0
        
        if abs(f(c)) < epsilon:  # Check if f(c) is close enough to zero
            return c
        elif f(c) * f(b) < 0:
            a = c
        else:
            b = c
    
    return (a + b) / 2

def newton(a,b,f):
    pass

