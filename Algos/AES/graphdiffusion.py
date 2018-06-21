import matplotlib.pyplot as plt

def drawGraph(L):
    X = [ i/100 for i in range(0, 100) ]
    Y = [ 0 ] * 100

    for l in L:
       Y[int(l/128*100)] += 1

    Y_ = [y/len(L) for y in Y]
      
    plt.plot(X , Y_)
    
    plt.legend(bbox_to_anchor=(0., 1, 1., .2), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
    
    plt.ylabel('Distribution normalisée')
    plt.show()

