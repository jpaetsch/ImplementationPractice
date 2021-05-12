seedCost = float(input())
lawnNumber = int(input())
totalCost = 0
for i in range(lawnNumber):
    width, length = input().split()
    width = float(width)
    length = float(length)
    totalCost += width*length*seedCost
print('%.7f'%totalCost)
