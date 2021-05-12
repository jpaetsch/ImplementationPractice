stoneNum = int(input())
winner = ""

if(stoneNum % 2 == 1):
    winner = "Alice"
else:
    winner = "Bob"

print(winner)