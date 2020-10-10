#CAVIT CAKIR 23657 HW3
'''places = [[[1, 0, 1]]]
memos = list()

for i in range(1,10):
    places.append(functions.buildIt(i))
#memos.append(funcDeneme.createMemo(places[i]))


for i in range(1,9):
    print(places[i])
    print("")

print(places[3])'''


import matplotlib.pyplot as plt
import functions


naiveArray = [0, 0, 0, 0, 0]
iterArray = [0, 0, 0, 0, 0]
topDownArray = [0, 0, 0, 0, 0]

for i in range(100):
    places7 = functions.buildIt(7)
    places10 = functions.buildIt(10)
    places15 = functions.buildIt(15)
    places17 = functions.buildIt(17)
    places20 = functions.buildIt(20)



    places200 = functions.buildIt(200)
    places400 = functions.buildIt(400)
    places600 = functions.buildIt(600)
    places800 = functions.buildIt(800)
    places1000 = functions.buildIt(1000)

    memoIt200 = functions.createMemo(places200)
    memoTb200 = functions.createMemo(places200)
    memoIt400 = functions.createMemo(places400)
    memoTb400 = functions.createMemo(places400)
    memoIt600 = functions.createMemo(places600)
    memoTb600 = functions.createMemo(places600)
    memoIt800 = functions.createMemo(places800)
    memoTb800 = functions.createMemo(places800)
    memoIt1000 = functions.createMemo(places1000)
    memoTb1000 = functions.createMemo(places1000)


    na7,optim = functions.na(places7)
    na10,optim = functions.na(places10)
    na15,optim = functions.na(places15)
    na17,optim = functions.na(places17)
    na20,optim = functions.na(places20)


    it200,optim = functions.it(memoIt200)
    tb200,optim = functions.tb(places200, memoTb200)

    it400,optim = functions.it(memoIt400)
    tb400,optim = functions.tb(places400, memoTb400)

    it600,optim = functions.it(memoIt600)
    tb600,optim = functions.tb(places600, memoTb600)

    it800,optim = functions.it(memoIt800)
    tb800,optim = functions.tb(places800, memoTb800)

    it1000,optim = functions.it(memoIt1000)
    tb1000,optim = functions.tb(places1000, memoTb1000)


    naiveArray[0] += na7
    naiveArray[1] += na10
    naiveArray[2] += na15
    naiveArray[3] += na17
    naiveArray[4] += na20

    iterArray[0] += it200
    iterArray[1] += it400
    iterArray[2] += it600
    iterArray[3] += it800
    iterArray[4] += it1000

    topDownArray[0] += tb200
    topDownArray[1] += tb400
    topDownArray[2] += tb600
    topDownArray[3] += tb800
    topDownArray[4] += tb1000



print("")
print(naiveArray)
print(iterArray)
print(topDownArray)

naiveArray[0] = naiveArray[0] / 100
naiveArray[1] = naiveArray[1] / 100
naiveArray[2] = naiveArray[2] / 100
naiveArray[3] = naiveArray[3] / 100
naiveArray[4] = naiveArray[4] / 100

iterArray[0] = iterArray[0] / 100
iterArray[1] = iterArray[1] / 100
iterArray[2] = iterArray[2] / 100
iterArray[3] = iterArray[3] / 100
iterArray[4] = iterArray[4] / 100

topDownArray[0] = topDownArray[0] / 100
topDownArray[1] = topDownArray[1] / 100
topDownArray[2] = topDownArray[2] / 100
topDownArray[3] = topDownArray[3] / 100
topDownArray[4] = topDownArray[4] / 100



xForNaive = [7,10,15,17,20]
xForOthers = [200,400,600,800,1000]
plt.plot(xForNaive,naiveArray)
plt.title('Naive')
plt.ylabel('Second')
plt.xlabel('Input Size')
plt.show()

plt.plot(xForOthers,iterArray)
plt.title('Iterative')
plt.ylabel('Second')
plt.xlabel('Input Size')
plt.show()

plt.plot(xForOthers,topDownArray)
plt.title('Top Bottom')
plt.ylabel('Second')
plt.xlabel('Input Size')
plt.show()





