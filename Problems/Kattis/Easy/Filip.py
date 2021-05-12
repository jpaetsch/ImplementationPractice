a, b = input().split()

# Method One
# a = ''.join(reversed(a))
# b = ''.join(reversed(b))

# Method Two
a = a[3::-1]
b = b[3::-1]

# Method Three
# Keep track of index, use a loop to append

if(a>b):
    print(a)
elif(b>a):
    print(b)
else:
    print('ERROR')