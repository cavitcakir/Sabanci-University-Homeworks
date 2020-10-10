#CAVIT CAKIR 23657 HW3
import functions as fn
n = 8
places = fn.buildIt(n)

for i in range(len(places)):
    print(places[i], "     ")

memoTb = fn.createMemo(places)
memoIt = fn.createMemo(places)

timeNa,opNa = fn.na(places)
timeTb,opTb = fn.tb(places,memoTb)
timeIt,opIt = fn.it(memoIt)
print("")
print("Native time =" , timeNa, "Optimal=", opNa)
print("")
print("TopBottom time=" , timeTb,"Optimal=",opTb)
print("")
print("Iterative time=" , timeIt,"Optimal=", opIt)
