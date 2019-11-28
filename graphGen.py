import random

def numGen(low, high, f):
    #for every 1000, create nodes that have edges in this range
    for i in range(low, high+1):
        #node
        f.write(str(i))
        f.write("\n")
        #random adjs
        added = []
        for j in range(5):
            toAdd = random.randint(low, high)
            if toAdd not in added:
                added.append(toAdd)
                f.write(str(toAdd))
                f.write("\n")
        #make sure all nodes are an adjaceny, so add every node as adjaceny of previous node
        toAdd = i + 1
        #if end of range, add first node in range
        if toAdd == high + 1:
            toAdd = low
        #if it has not been added yet
        if toAdd not in added:
            f.write(str(toAdd))
            f.write("\n")
        #-1 to indicate next node
        f.write(str(-1))
        f.write("\n")

def main():
    numNodes = int(input("Enter desired number of nodes: "))
    f = open("large1.txt", "w")
    for i in range(0, numNodes, numNodes//10):
        numGen(i, i+(numNodes//10)-1, f)
    f.close()

main()
