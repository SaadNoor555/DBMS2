import math

class_index = 0

def split_rows(dimension, value, parent):
    left, right = list(), list()

    for row in parent:
        if float(row[dimension]) < float(value):
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
        class_rows[int(row[class_index])-1] += 1
    
    return class_rows

def get_n_column(row):
    n_col=0
    for col in row:
        n_col+=1
    return n_col

def entropy(group, n_class):
    entropy = 0
    tot_rows = int(get_tot_rows(group))
    class_rows = get_class_rows(group, n_class)
    if tot_rows<=0:
        return 0
    for x in class_rows:
        prob = float(x/tot_rows)
        if(prob>0):
            entropy += (prob * math.log(prob))
    return -entropy

def info_gain(parent, left, right, n_class):
    parent_entropy = entropy(parent, n_class)
    left_entropy = entropy(left, n_class)
    right_entropy = entropy(right, n_class)

    parent_rows = get_tot_rows(parent)
    left_rows = get_tot_rows(left)
    right_rows = get_tot_rows(right)

    info_gain = parent_entropy - ((left_rows/parent_rows)*left_entropy + (right_rows/parent_rows)*right_entropy)
    return info_gain

def select_split(parent, n_class):
    best_gain = 0.0
    best_val= 0.0
    best_dim= 0
    gain= 0
    n_col = get_n_column(parent[0])
    for row in parent:
        for col in range(1, n_col):
            left, right=split_rows(col, row[col], parent)
            gain= info_gain(parent, left, right, n_class)
            if float(best_gain)<gain:
                best_val= row[col]
                best_dim= col
                best_gain=gain

    return best_dim, best_val