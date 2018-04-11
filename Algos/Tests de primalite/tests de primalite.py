from random import random, randint
import math
import timeit
from time import time

def is_prime_impair(n):
    return all(n % i for i in range(3, int(math.sqrt(n)) + 1, 2))



# n impair
def J_getPowTwoVal(n):
    if n % 8 == 3 or n % 8 == 5:
        return -1
    return 1

# pour n et m impairs
def J_switchVal(j):
    (sign, m, n) = j
    if m % 4 == 3 and n % 4 == 3:
        sign *= -1
    return (sign, n, m)

# n impair
def J_reducePowTwo(j):
    k = 0
    (sign, m, n) = j
    while m & 1 == 0:
        m = m >> 1
        k += 1
    if k % 2 == 0:
        return (sign, m, n)
    return (J_getPowTwoVal(n)*sign, m, n)

# n impair
def J_mod(j):
    (sign, m, n) = j
    return (sign, m % n , n)

# n impair
def Jacobi(m, n):
    j = (1, m, n)
    (sign, m, n) = j
    while m > 1:
        (sign, m, n) = j
        if m > n:
            j = J_mod(j) 
        elif m % 2 == 0:
            j = J_reducePowTwo(j)
        else:
            j = J_switchVal(j)
        (sign, m, n) = j
    return sign*m




def Solovay_Strassen_aux(n, a):
    x = Jacobi(a,n)
    if x == 0:
        return False
    y = pow(a, (n-1)//2, n)
    if (x - y) % n == 0:
        return True
    return False

#n impair
def Solovay_Strassen(n, nbTests = 100):
    for i in range(nbTests):
        a = randint(1, n-1)
        if not Solovay_Strassen_aux(n, a):
            return False
    return True
    
    
    
    
def Miller_Rabin_aux(n, a, k, m):
    a = randint(1, n-1)
    b = pow(a, m, n)
    if b == 1:
        return True
        
    for i in range(0,k):
        if b == n-1:
            return True
        b = (b*b) % n
    return False

#n impair
def Miller_Rabin(n, nbTests = 100):
    k = 0
    m = n - 1
    while m & 1 == 0:
        m = m >> 1
        k += 1
    # n-1 = 2^k*m
    
    for i in range(nbTests):
        a = randint(1, n-1)
        if not Miller_Rabin_aux(n, a, k, m):
            return False
    return True

    
import matplotlib.pyplot as plt
from numpy import log


def compareResults(algo1, algo2, start, NB = 100000):

    def testalg(alg, X, Y, NB):
        t = time()
        n = 0
        for i in range(NB):
            x = X[i]
            if alg(x):
                n += 1
            Y[i] = n
        return (n, time()-t)
        
    X = [i for i in range(start,2*NB+start,2)]
    
    Y1 = [0]*NB
    Y2 = [0]*NB
    Y3 = [0]*NB
    Y4 = [0]*NB
    Y5 = [0]*NB
    Y6 = [0]*NB
    
    print(testalg(algo1, X, Y1, NB))
    print(testalg(algo2, X, Y2, NB))
    print(testalg(is_prime_impair, X, Y3, NB))
    
    plt.plot(X,Y1)
    plt.plot(X,Y2)
    plt.plot(X,Y3)
    
    plt.ylabel('Nombres de positifs')
    plt.show()

def compareTime(algo1, algo2, start, NB= 10000):
    CHUNK_SIZE = 1000
    
    def testalg(alg, x):
        start_time = timeit.default_timer()
        for i in range(x, x + CHUNK_SIZE):
            alg(x)
        return (timeit.default_timer() - start_time)/CHUNK_SIZE
            
    X = [ i for i in range(1,NB,CHUNK_SIZE)]  
      
    Y1 = [ testalg(algo1, x) for x in X]
    Y2 = [ testalg(algo2, x) for x in X]
    Y3 = [ testalg(is_prime_impair, X[i:i+CHUNK_SIZE]) for i in range(1,NB,CHUNK_SIZE)]
    
    
    plt.plot(Xn,Y1, label = "Algo 1")
    plt.plot(Xn,Y2, label = "Algo 2")
    plt.plot(Xn,Y3, label = "Algo naif")
    
    plt.legend(bbox_to_anchor=(0., 1, 1., .2), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
    
    plt.ylabel('Temps')
    plt.show()
