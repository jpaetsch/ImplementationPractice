# Merge Two Sorted Lists

# You are given the heads of two sorted linked lists list1 and list2.
# Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
# Return the head of the merged linked list.

# Example 1:
# Input: list1 = [1,2,4], list2 = [1,3,4]
# Output: [1,1,2,3,4,4]

# Example 2:
# Input: list1 = [], list2 = []
# Output: []

# Example 3:
# Input: list1 = [], list2 = [0]
# Output: [0]

# The number of nodes in both lists is in the range [0, 50].
# -100 <= Node.val <= 100
# Both list1 and list2 are sorted in non-decreasing order.

# ---

from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


# Iterative and in-place solution
# Time Complexity = ??  | Space Complexity = ??  
class Solution1:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:

        head = ListNode(0)
        current = head

        # When there are items to be sorted in both, create the merged one by iterating through
        while list1 and list2:
            if list1.val < list2.val:
                current.next = list1
                list1 = list1.next
            else:
                current.next = list2
                list2 = list2.next
            current = current.next
        
        # Set the elements of the remaining list to the merged one and return the true start of the merged list
        current.next = list1 or list2
        return head.next

# ---


# Recursive solution
# Time Complexity = ??  | Space Complexity = ??
class Solution2:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:

        if not list1 or not list2:
            return list1 or list2
        if list1.val < list2.val:
            list1.next = self.mergeTwoLists(list1.next, list2)
            return list1
        else:
            list2.next = self.mergeTwoLists(list1, list2.next)
            return list2
        
# ---