import math

def split(dimension, value, parent):
    left, right = list(), list()

    for row in parent:
        if row[dimension] < value:
            left.append(row)
        else:
            right.append(row)
    
    return left, right

def get_tot_rows(group):
    tot_rows = 0
    for row in group:
        tot_rows += 1
    
    return tot_rows

def get_class_rows(group, n_class):
    class_rows = [0]*n_class
    for row in group:
        class_rows[row[0]-1] += 1
    
    return class_rows

def entropy(group, n_class):
    entropy = 0
    tot_rows = get_tot_rows(group)
    class_rows = get_class_rows(group, n_class)

    for x in class_rows:
        entropy += (x/tot_rows) * math.log(x/tot_rows, 2)

    return entropy

def info_gain(parent, left, right, n_class):
    parent_entropy = entropy(parent, n_class)
    left_entropy = entropy(left, n_class)
    right_entropy = entropy(right, n_class)

    parent_rows = get_tot_rows(parent)
    left_rows = get_tot_rows(left)
    right_rows = get_tot_rows(right)

    info_gain = parent_entropy - ((left_rows/parent_rows)*left_entropy + (right_rows/parent_rows)*right_entropy)
    return info_gain
