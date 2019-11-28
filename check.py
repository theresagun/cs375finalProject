def main():
    stringToCheck = input("Enter string to check: ")
    rangeCheck = int(input("Enter range start val: "))
    for i in range(rangeCheck, rangeCheck+101):
        if stringToCheck.count(str(i)) != 1:
            print(i)
main()
