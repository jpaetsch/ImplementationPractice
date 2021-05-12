monthlyLimit = int(input())
numLines = int(input())
output = 0

# calculate data carryover
for i in range(numLines):
    currentMonth = int(input())
    output += monthlyLimit - currentMonth

# for the n + 1 month's data increase
output += monthlyLimit

print(output)