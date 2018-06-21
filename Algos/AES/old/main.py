from math_helper import *

# St : texte clair, K: clef
def AES(St, K): 
    TK = KeyExpansion(K) ;
    St = AddRoundKey(St, TK[0]) ;
    for i in range(1, Ne):
        St = Round(St, TK[i])
    St = FinalRound(St, TK[Ne])
    return St
    
    
def Round(St, T):
    St = SubBytes(St)
    St = ShiftRows(St)
    St = MixColumns(St)
    St = AddRoundKey(St, T)
    return St
    
def FinalRound(St, T):
    St = SubBytes(St)
    St = ShiftRows(St)
    St = AddRoundKey(St, T)
    return St


def KeyExpansion(K):
    pass


def AddRoundKey(St, T):
    return St * T           # multiplication = xor
    
    
def SubBytes(St):
    return AES_SBox.transform(St)
    
    
def ShiftRows(St):
    return St.shiftRows()
    
    
def MixColumns(St):
    pass

