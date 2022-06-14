# 1. Longest Common Prefix

# Write a function to find the longest common prefix string amongst an array of strings.
# If there is no common prefix, return an empty string "".

# EXAMPLES
# Example 1:
# Input: strs = ["flower","flow","flight"]
# Output: "fl"

# Example 2:
# Input: strs = ["dog","racecar","car"]
# Output: ""
# Explanation: There is no common prefix among the input strings.

# ---
from typing import List

# A bit clunky and slow compared to other methods but completely my own work
# Should potentially use enumerate instead
# Time Complexity = O(n*m) | Space Complexity = O(n)
class SolutionOne:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        prefix = ""
        
        smallestPossible = min(strs,key=len)
        
        for i in range(len(smallestPossible)):
            for word in strs:
                if word[i] != smallestPossible[i]:
                    return prefix
            prefix += smallestPossible[i]
        
        return prefix

# ---

# Although O times wouldn't change by an order of magnitude, this code is much more efficient
# and scored better than most other solutions - good practice slicing arrays and utilizing enumerate
class SolutionTwo:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        
        smallestPossible = min(strs,key=len)
        
        for idx, val in enumerate(smallestPossible):
            for word in strs:
                if word[idx] != val:
                    return smallestPossible[:idx]

        return smallestPossible



if __name__ == '__main__':

    testOne = ["flower","flow","flight"]
    testTwo = ["dog","racecar","car"]

    # s = SolutionOne()
    # s.longestCommonPrefix(testOne)

    s = SolutionTwo()
    s.longestCommonPrefix(testOne)