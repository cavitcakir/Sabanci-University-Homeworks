#CAVIT CAKIR 23657 HW3
from timeit import default_timer as timer
import sys
import random

one = [0,0,0]
two = [1,0,0]
three = [0,1,0]
four = [0,0,1]

possibleLanes=list()
possibleLanes.append(one)
possibleLanes.append(two)
possibleLanes.append(three)
possibleLanes.append(four)

def buildIt(n):
    myList = list()
    myList.append([1,0,1])
    for i in range(n-1):
       myList.append(possibleLanes[random.randint(0,3)])
    #for i in range(len(myList)):
     #   print(myList[i], "     ")
    #print("I am done -WorkerFromFarAway    n:",n )
    return myList

def createMemo(myList):
    n = len(myList)
    myMemo = list()
    myMemo.append([n + 1, 0, n + 1])
    for i in range(len(myList) - 1):
        myMemo.append([-1, -1, -1])
        for j in range(3):
            if myList[i + 1][j] == 1:
                myMemo[i + 1][j] = n + 1
    return myMemo

def it(myMemo):
    if(len(myMemo) == 1):
        return 0,0
    #print("")
    #print("")
    #print("------Iterative--------")
    start = timer()
    for i in range(1 , len(myMemo)):
       for j in range(len(myMemo[i])):
          if myMemo[i][j] == -1:
             if j==0:
                 myMemo[i][j] = min(myMemo[i-1][0],myMemo[i-1][1] + 1 )
             elif j == 2:
                 myMemo[i][j] = min(myMemo[i - 1][2], myMemo[i - 1][1] + 1)
             else :
                 myMemo[i][j] = min(myMemo[i - 1][1], myMemo[i - 1][2] + 1,myMemo[i - 1][0] + 1)

    x=min(myMemo[len(myMemo)-1][0],myMemo[len(myMemo)-1][1],myMemo[len(myMemo)-1][2])
    end = timer()

    #print("Time:",end - start)
    #print("Optimal: ",x)
    diff = end - start
    return diff,x


def checkMemo(l, c, n, places, myMemo):
    if myMemo[l][c] != -1:
        return myMemo[l][c]
    else:
        myMemo[l][c] = topBottomR(l,c, n, places, myMemo)
        return myMemo[l][c]

def topBottomR(l, c, n, places, myMemo):

    if l == 0:
        if c == 1:
            return 0
        else:
            return n+1

    if places[l][c] == 1:
        return n+1

    if c == 0:
        return min(checkMemo(l-1,c,n,places, myMemo), (checkMemo(l-1,c+1,n,places, myMemo) + 1))
    elif c == 2:
        return min(checkMemo(l - 1, c,n,places, myMemo), (checkMemo(l - 1, c - 1,n,places, myMemo) + 1))
    else:
        return min(checkMemo(l-1,c,n,places, myMemo), (checkMemo(l-1,c-1,n,places, myMemo) + 1) , (checkMemo(l-1,c+1,n,places, myMemo) + 1))


def tb(places,myMemo):
    if (len(places) == 0):
        return 0, 0
    n = len(places)
    sys.setrecursionlimit(10000000)
    start = timer()
    a = topBottomR(n - 1, 0, n, places, myMemo)
    b = topBottomR(n - 1, 1, n, places, myMemo)
    c = topBottomR(n - 1, 2, n, places, myMemo)
    optimal = min(a, b, c)
    end = timer()
    #print("")
    #print("----topBottom----")
    #print("Time:", end - start)
    #print("Optimal:", optimal)
    diff = end - start
    return diff, optimal


def naiveCall(l, c,places,n):
    if l == 0:
        if c == 1:
            return 0
        else:
            return n+1

    if places[l][c] == 1:
        return n+1

    if c == 0:
        return min(naiveCall(l-1,c,places,n), (naiveCall(l-1,c+1,places,n) + 1))
    elif c == 2:
        return min(naiveCall(l - 1, c,places,n), (naiveCall(l - 1, c - 1,places,n) + 1))
    else:
        return min(naiveCall(l-1,c,places,n), (naiveCall(l-1,c-1,places,n) + 1) , (naiveCall(l-1,c+1,places,n) + 1))

def na(places):
    if (len(places) == 0):
        return 0, 0
    n = len(places)
    start = timer()
    a = naiveCall(n-1,0,places,n)
    b = naiveCall(n-1,1,places,n)
    c = naiveCall(n-1,2,places,n)
    optimal = min(a,b,c)
    end = timer()
    #print("")
    #print("----Naive----")
    #print("Time:",end - start)
    #print("Optimal:", optimal)
    diff = end - start
    return diff, optimal