stoneNum = int(input())
winner = ""

# Use modulus to check the remainder
if(stoneNum % 2 == 1):
    winner = "Alice"
else:
    winner = "Bob"

print(winner)