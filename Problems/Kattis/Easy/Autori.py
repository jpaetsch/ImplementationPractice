# Split input along the hyphen delimiter
individualNames = input().split("-")

# Append the first letter of each name into the output string
outputString = ""
for name in individualNames:
    outputString += name[0]

print(outputString)
