from typing import List

# Python snippet that uses recursion to generate all permutations of an integer array input
# Can also use itertools library (recommended)
# Ex: [0,1,2] -> [[0,1,2],[0,2,1],[1,0,2],[1,2,0],[2,0,1],[2,1,0]]
def getPermutations(self, currentList: List[int]) -> List[List[int]]:

    # Recursion terminal cases
    if len(currentList) == 0:
        return []
    if len(currentList) == 1:
        return [currentList]
    
    l = []    # Hold the current permutation based on the first number
    for i in range(len(currentList)):
        m = currentList[i]    # For each number, use it as the starting number
        remainingList = currentList[:i] + currentList[i+1:]    # Get the remaining elements as a list
    
        for p in self.getPermutations(remainingList):    # Recursively get permutations, appending to the list of lists
            l.append([m] + p)