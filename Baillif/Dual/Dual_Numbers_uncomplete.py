import numpy as np


### Classe de nombres duaux, AVEC DES TROUS.

### S'initialise en écrivant par exemple:
### u = Dual_Numbers( real = 2 , dual = 3) pour u = 2 + 3epsilon, ou plus simplement
### u = Dual_Numbers( 2 , 3 )
### Si u est un Dual_Numbers, u.r est sa partie réelle et u.d sa partie duale.
### L'addition et la multiplication peuvent combiner des int/float avec des Dual_Numberss.
### La soustraction et la division sont définies avec la négation simple et l'inverse multiplicatif
### en utilisant l'addition et la multiplication. Elles peuvent donc également combiner des 
### int/floats avec des Dual_Numberss.


class Dual_Numbers:
    
    #### Fonction d'initialisation de la classe.
    def __init__(self, real = 1 , dual = 0):
        self.r = real
        self.d = dual
    
    #### Fonction qui définit le string d'un nombre dual lorsqu'on le print.
    def __str__(self):
        if self.r == 0:
           if self.d == 0: return "0"
           else: return str(self.d) + "\u03B5"
        elif self.d == 0:
           return str(self.r) 
        else:     
           if self.d > 0: sym = "+"
           else: sym = "-"
           return str(self.r) + sym + str(abs(self.d)) + "\u03B5"
        
    ############### Surcharge des opérateurs ###################
    
    ### Addition a.__add__(b)
    def __add__(a, b):
        ### Cette partie assure que si l'on a un float ou un int, on le transforme en Dual_Numbers avant de faire l'opération,
        ### que l'on doit alors faire avec les nombres duaux a et b2.
        if type(b) in [int,float]:
           b2 = Dual_Numbers( real = b )
        else:
           b2 = b
        ### Fin de la partie pour assurer la compatibilité entre int/float et Dual_Numberss
        
        return Dual_Numbers( real = a.r + b2.r , dual = a.d + b2.d )
    
    ### Addition a.__radd__(b)
    __radd__ = __add__
    
    
    ### négation simple
    def __neg__(a):
        if type(a) in [int,float]:
           return -a
        else:
           return Dual_Numbers( real = -a.r , dual = -a.d )
    
    ### soustraction a.__sub__(b)
    def __sub__(a,b):
        return a + b.__neg__()
        
    ### soustraction a.__rsub__(b)
    def __rsub__(a,b):
        return b + a.__neg__()
    
    ### multiplication a.__mul__(b)
    def __mul__(a, b):
        ### Cette partie assure que si l'on a un float ou un int, on le transforme en Dual_Numbers avant de faire l'opération,
        ### que l'on doit alors faire avec les nombres duaux a et b2.
        if type(b) in [int,float]:
           b2 = Dual_Numbers( real = b , dual = 0)
        else:
           b2 = b
        ### Fin de la partie pour assurer la compatibilité entre int/float et Dual_Numberss
        
        return Dual_Numbers(real=a.r * b2.r, dual = (a.r * b2.d) + (a.d * b2.r))

    ### multiplication a.__rmul__(b)        
    __rmul__ = __mul__
       
    ### definition de 1/a 
    def mult_inverse(a):
        if type(a) in [int,float]:
          return 1/a
        elif a.r == 0: 
            raise TypeError(f"Division par un élément non-inversible :{a}" )
        else: 
            return Dual_Numbers(real=1.0/a.r, dual=((a.d)/(-a.r**2)))
     
     
     
    ### division a/b : a.__truediv__(b) 
    def __truediv__(a,b):
        return a * Dual_Numbers.mult_inverse(b)
        
    ### division b/a : a.__rtruediv__(b)
    def __rtruediv__(a,b):
        return Dual_Numbers.mult_inverse(a) * b
    
    
    ### COS
    def cos(a):        
        if type(a) in [int,float]:
            return Dual_Numbers(real = np.cos(a), dual = 0)
        else:
            return Dual_Numbers( real = np.cos(a.r) , dual = -np.sin(a.r) * a.d)
    
    def sin(a):
        if type(a) in [int,float]:
            return Dual_Numbers(real= np.sin(a), dual = 0)
        else:
            return Dual_Numbers(real = np.sin(a.r), dual = np.cos(a.r) * a.d)

    def exp(a):
        if type(a) in [int,float]:
            return Dual_Numbers(real = np.exp(a), dual = 0)
        else:
            return Dual_Numbers(real = np.exp(a.r), dual = np.exp(a.r) * a.d)
    
    def log(a):
        if type(a) in [int,float]:
            return Dual_Numbers(real=np.log(a), dual = 0)
        else:
            return Dual_Numbers(real = np.log(a.r), dual = (1/a.r) * a.d)
