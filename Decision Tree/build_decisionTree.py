import splitter as SP

class DecisionTree:
    def __init__(self, rows, div_dim, div_val):
        self.data = rows
        self.dim, self.val = div_dim, div_val
        self.leftChild, self.rightChild= None, None

def build_decision_tree(parent, n_class):
    best_dim, best_val= SP.select_split(parent, n_class)
    left, right= SP.split_rows(best_dim, best_val, parent)
    leftNode= DecisionTree(left, 0, 0.0)
    rightNode= DecisionTree(right, 0, 0.0)
    if SP.entropy(left, n_class)!=0 and SP.get_tot_rows(left)>1:
        leftNode = build_decision_tree(left, n_class)
    if SP.entropy(right, n_class)!=0 and SP.get_tot_rows(right)>1:
        rightNode = build_decision_tree(right, n_class)

    parentNode = DecisionTree(parent, best_dim, best_val)
    parentNode.leftChild= leftNode
    parentNode.rightChild= rightNode
    return parentNode