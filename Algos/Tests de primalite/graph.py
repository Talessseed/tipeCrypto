import matplotlib.pyplot as plt

def compareTime(filepath, ptNb, nb):
    nb = int(nb)
    ptNb = int(ptNb)
    step = nb//ptNb
    file = open(filepath, "r")
    
    X = [ i for i in range(3, nb+step, step*5)]
    Y1 = []
    Y2 = []
    Y3 = []
    A1 = []
    A2 = []
    A3 = []

    lines = file.readlines()
    for i in range(3,len(lines), 25):
        A1 = []
        A2 = []
        A3 = [] 
        for j in range(i,max(len(lines),i+50), 5):
            A1.append(lines[i])
            A2.append(lines[i+1])
            A3.append(lines[i+2])
        a1 = 0
        a2 = 0
        a3 = 0
        for i in range(len(A1)):
            a1 += int(A1[i])
            a2 += int(A2[i])
            a3 += int(A3[i])
        Y1.append(a1/len(A1))
        Y2.append(a2/len(A1))
        Y3.append(a3/len(A1))
  
    file.close()
    
    plt.plot(X ,Y1, label = "Algorithme naif")
    plt.plot(X ,Y2, label = "Solovay Strassen")
    plt.plot(X ,Y3, label = "Miller Rabin")
    
    plt.legend(bbox_to_anchor=(0., 1, 1., .2), loc=3,
           ncol=2, mode="expand", borderaxespad=0.)
    
    plt.ylabel('Temps')
    plt.show()
