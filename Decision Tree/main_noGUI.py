from distutils.command.build import build
from imghdr import tests
import build_decisionTree as DT
import converter as CON
import splitter as SP
import csv
import easygui
import random

def findAppropriateNode(node ,data):
    if node.dim == 0:
        return node.data[0][0]
    if float(data[node.dim])<float(node.val):
        return findAppropriateNode(node.leftChild, data)
    else:
        return findAppropriateNode(node.rightChild, data)

def testDecisionTree(root, testset):
    r_ans, tot_test= 0, 0
    for row in testset:
        cls= findAppropriateNode(root, row)
        if cls == row[0]:
            r_ans+=1
        tot_test+=1
    return r_ans, tot_test

def divDataset(idx, sz, dataset):
    trainSet, testset= [], []
    i=0
    for row in dataset:
        if i>=idx and i<idx+(sz/10):
            testset.append(row)
        else:
            trainSet.append(row)
        i+=1
    return trainSet, testset

def printPreOrder(node, depth=0):
    if node.leftChild!=None:
        printPreOrder(node.leftChild, depth+1)
    if node.rightChild!=None:
        printPreOrder(node.rightChild, depth+1)
    for i in range(depth): print(end='-')        
    print(node.dim, ', ', node.val)

'''driver starts here'''
file = open('wine.csv')
csvreader = csv.reader(file)
dataset = []
for row in csvreader:
    dataset.append(row)
n_class=3
random.shuffle(dataset)
g_tot, g_r_tol= 0,0
for i in range(10):
    sz= len(dataset)
    trainSet, testset = divDataset(i*(sz/10), sz, dataset)
    root = DT.build_decision_tree(trainSet, n_class)
    r_ans, tot_test= testDecisionTree(root, testset)
    g_tot+=tot_test
    g_r_tol+=r_ans
    ac= (r_ans/tot_test)*100
    print('Test '+str(i+1)+' Accuracy: '+str(ac))
printPreOrder(root)
g_acc=(g_r_tol/g_tot)*100
msg='\nAccuracy: '+str(g_acc)+'%\n'+'Total testset size: '+str(g_tot)
print(msg)
file.close()