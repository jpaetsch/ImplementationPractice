inp = input().split()
x = int(inp[0])
y = int(inp[1])
N = int(inp[2])

# Loop through and test values with modulus to provide label
for i in range(1, N+1):
    if(i % x == 0):
        if(i % y == 0):
            print('FizzBuzz')
        else:
            print('Fizz')
    elif(i % y == 0):
        print('Buzz')
    else:
        print(str(i))