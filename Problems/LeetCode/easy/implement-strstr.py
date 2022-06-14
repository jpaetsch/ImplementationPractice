# Implement strStr()

# Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
# Clarification:
# What should we return when needle is an empty string? This is a great question to ask during an interview
# For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

# Example 1:
# Input: haystack = "hello", needle = "ll"
# Output: 2

# Example 2:
# Input: haystack = "aaaaa", needle = "bba"
# Output: -1

# Constraints:
# 1 <= haystack.length, needle.length <= 104
# haystack and needle consist of only lowercase English characters.

# ---

# My simple solution iterating over the string using a sliding window
# Time Complexity = ??  | Space Complexity = ??
class Solution1:
    def strStr(self, haystack: str, needle: str) -> int:
        
        # Clarification edge case
        if needle == '':
            return 0
        
        # Other obvious cases
        if len(needle) > len(haystack):
            return -1
        elif len(needle) == len(haystack):
            if needle != haystack:
                return -1
            else:
                return 0
        
        # Sliding window to check substrings
        ptrOne = 0
        ptrTwo = len(needle)
        
        while ptrTwo <= len(haystack):
            if haystack[ptrOne:ptrTwo] == needle:
                return ptrOne
            else:
                ptrOne += 1
                ptrTwo += 1
        
        return -1

# ---

# Could use the Python standard find() function: haystack.find(needle)
# Could also use Rabin Karp (built-in, custom, rolling hash) or KMP algorithms to do substring searching