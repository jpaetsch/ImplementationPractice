# Palindrome Number

# Given an integer x, return true if x is palindrome integer.
# An integer is a palindrome when it reads the same backward as forward.
# For example, 121 is a palindrome while 123 is not.

# Example 1:
# Input: x = 121
# Output: true
# Explanation: 121 reads as 121 from left to right and from right to left.

# Example 2:
# Input: x = -121
# Output: false
# Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

# Example 3:
# Input: x = 10
# Output: false
# Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

# ---

# My solution, iterates using two pointers from either end to meet in the middle
# A bit slow and clunky...
# Time Complexity = O(log(N))  | Space Complexity = O(N) for string replacement...
class Solution1:
    def isPalindrome(self, x: int) -> bool:
        stringified = str(x)
        
        if len(stringified == 1):
            return True

        ptrOne = 0
        ptrTwo = len(stringified) - 1

        while ptrOne < ptrTwo:
            if stringified[ptrOne] != stringified[ptrTwo]:
                return False
            ptrOne += 1
            ptrTwo -= 1
        
        return True

# ---

# Follow up: Could you solve it without converting the integer to a string?

# Their solution, which applies the follow-up and reverts half of the number
# Less memory usage
# Time Complexity = O(log(N))  | Space Complexity = O(1)
class Solution2:
    def isPalindrome(self, x: int) -> str:
        if x < 0 or (x % 10 == 0 and x != 0):
            return False
        
        revertedNumber = 0
        while x > revertedNumber:
            revertedNumber = revertedNumber * 10 + x % 10
            x = x // 10

        return x == revertedNumber or x == revertedNumber // 10

# ---


if __name__ == '__main__':

    testOne = 121
    testTwo = -121
    testThree = 4200
    testFour = 11

    s = Solution2()
    s.isPalindrome(testFour)