# Valid Parentheses

# Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
# An input string is valid if:
# Open brackets must be closed by the same type of brackets.
# Open brackets must be closed in the correct order.

# Example 1:
# Input: s = "()"
# Output: true

# Example 2:
# Input: s = "()[]{}"
# Output: true

# Example 3:
# Input: s = "(]"
# Output: false

# ---

# My very simple solution that just iterates through the characters, keeping the last open bracket and
# number of open brackets to ensure rules are enforced
# Time Complexity = O(N)  (is string operations O(1) ??)  | Space Complexity = O(N)
class Solution1:
    def isValid(self, s: str) -> bool:

        strLength = len(s)
        
        # Catch obvious rule breaks early
        if strLength == 1 or strLength % 2 != 0:
            return False
        
        stillOpen = ''

        for val in s:
            if val == '{' or val == '(' or val == '[':
                stillOpen += val
            else:
                lastParentheses = stillOpen[-1:]    # Get the last character of the string
                if val == '}':
                    if lastParentheses != '{':
                        return False
                    else:
                        stillOpen = stillOpen[:-1]  # Trim the last character of the string
                elif val == ')':
                    if lastParentheses != '(':
                        return False
                    else:
                        stillOpen = stillOpen[:-1]
                elif val == ']':
                    if lastParentheses != '[':
                        return False
                    else:
                        stillOpen = stillOpen[:-1]
                else:
                    return False
        
        if len(stillOpen) != 0:
            return False
        
        return True

# ---


# A better and quicker solution that implements a dictionary and basic stack
# Note that this works as the input is clean, would need to be modified to catch bad brackets
# Time Complexity = O(N) (push and pop is O(1) but iterate the string)  | Space Complexity = O(N)
class Solution2:
    def isValid(self, s: str) -> bool:

        # Catch obvious rule breaks early
        if len(s) % 2 != 0:
            return False

        # Set up a stack and dictionary of matching bracket pairs
        match = {'{':'}', '(':')', '[':']'}
        currentOpen = []
        for ch in s:
            if ch in match:     # Check the keys for open bracket
                currentOpen.append(ch)
            elif currentOpen == [] or match[currentOpen.pop()] != ch:   # If it is a close bracket, check for latest open bracket on the stack
                return False
        
        return currentOpen == []


# ---

if __name__ == '__main__':
    test1 = '()'
    test2 = '()[]{}'
    test3 = '(]'
    test4 = '{[]}'

    s = Solution1()
    print(s.isValid(test4))