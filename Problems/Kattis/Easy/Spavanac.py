inputNums = input().split()
hourNum = int(inputNums[0])
minNum = int(inputNums[1])

# first subtract minutes, then take care of edge cases for the clock
# flipping over in 24 hour format

if(minNum - 45 < 0):
    minNum = (minNum - 45) + 60
    if(hourNum - 1 < 0):
        hourNum = (hourNum - 1) + 24
    else:
        hourNum = hourNum - 1
else:
    minNum = minNum - 45

print(str(hourNum) + " " + str(minNum))
