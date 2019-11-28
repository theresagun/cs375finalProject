import random

def numGen(low, high, f):
    #for every 1000, create nodes that have edges in this range
    for i in range(low, high+1):
        #node
        f.write(str(i))
        f.write("\n")
        #random adjs
        added = []
        for i in range(5):
            toAdd = random.randint(low, high)
            if toAdd not in added:
                added.append(toAdd)
                f.write(str(toAdd))
                f.write("\n")
        #-1 to indicate next node
        f.write(str(-1))
        f.write("\n")

def main():
    numNodes = int(input("Enter desired number of nodes: "))
    f = open("large2.txt", "w")
    for i in range(0, numNodes, numNodes//10):
        numGen(i, i+(numNodes//10)-1, f)
    f.close()

main()
