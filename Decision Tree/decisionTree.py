import splitting

class DecisionTree:
    def __init__(self, rows):
        self.data = rows
        leftChild, rightChild = None, None

def build_decision_tree(parent, n_class):
    best_dim, best_val= splitting.select_split(parent.data, n_class)
    left, right= splitting.split(best_dim, best_val, parent.data)
    
    if(splitting.entropy(left, n_class)!=0):
        leftNode = build_decision_tree(left, n_class)
    if(splitting.entropy(right, n_class)!=0):
        rightNode = build_decision_tree(right, n_class)

    parentNode = DecisionTree(parent)
    parentNode.leftChild= leftNode
    parentNode.rightChild= rightNode
    return parentNode



root = build_decision_tree(dataset, n_class)