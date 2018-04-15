""" How to use :
>>> g = gf28Constructor()
>>> a = g(202)*g(83)
>>> print(a.value)
1
"""

def mulgf28(t, b):
    res = 0
    while (b != 0):
        if (b & 1) != 0:
            res ^= t            # res += t
        b = b >> 1
        carry = t & 0x80
        t = t << 1
        if carry != 0:
            t ^= 0x11b          # substract (= add) 0x11b from t
    return res

def gf28Constructor():
    E_ = [1]*256
    L_ = [0]*256
    p = 1
    for i in range(1,255):
        p = mulgf28(p,3)
        E_[i] = p
        L_[p] = i
    print(E_)
    print(L_)
    
    class Gf28:
        L = L_
        E = E_
        
        def __init__(self, value):
            self.value = value          # represented as a byte
            
        def __add__(self, other):
            return Gf28(self.value ^ other.value)
            
        def __radd__(self, other):
            return Gf28(self.value ^ other.value)
            
        def __str__(self):
            return bin(self.value)[2:]
            
        def __mul__(self, other):
            a = self.value
            b = other.value
            if a == 0 or b == 0: 
                return 0
            return Gf28(Gf28.E[ (Gf28.L[a] + Gf28.L[b]) % 255])
            
        def inv(self, x):
            return Gf28(Gf28.E[255 - Gf28.L[x]])
            
    return Gf28
