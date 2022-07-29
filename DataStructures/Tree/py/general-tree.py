class TreeNode:
    def __init__(self, val):
        self.val = val
        self.children = []

    def insert_child(self, child_node):
        self.children.append(child_node)

    def remove_child(self, child_node):
        self.children = [child for child in self.children if child is not child_node]

    def traverse(self):
        nodes_to_visit = [self]
        while len(nodes_to_visit) > 0:
            current_node = nodes_to_visit.pop()
            nodes_to_visit += current_node.children