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
        writer.writerow([row[0], cls, cls == row[0]])
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

def printPreOrder(node, depth):
    if node.leftChild!=None:
        printPreOrder(node.leftChild, depth+1)
    if node.rightChild!=None:
        printPreOrder(node.rightChild, depth+1)
    for i in range(depth): print(end='-')        
    print(node.dim, ', ', node.val)

'''driver starts here'''
file = open(CON.getFile())
csvreader = csv.reader(file)
dataset = []
for row in csvreader:
    dataset.append(row)

'''FOR GUI AND FILES'''
title = "Create Decision Tree"
text = "Enter number of class:"
n_class = int(easygui.enterbox(text, title))
title = "Enter File Name"
text = "Result File Name:"
d_text = "*.csv"
saveFileName = easygui.enterbox(text, title, d_text)
if saveFileName.endswith('.csv')==False:
    saveFileName += '.csv'
outputFile = open(saveFileName, 'w', newline='')
writer = csv.writer(outputFile)


random.shuffle(dataset)
g_tot, g_r_tol= 0,0
for i in range(10):
    writer.writerow(['Run:', i+1])
    writer.writerow(['expected', 'found', 'correctness'])
    sz= len(dataset)
    trainSet, testset = divDataset(i*(sz/10), sz, dataset)
    root = DT.build_decision_tree(trainSet, n_class)
    r_ans, tot_test= testDecisionTree(root, testset)
    g_tot+=tot_test
    g_r_tol+=r_ans
    ac= (r_ans/tot_test)*100
    print('Test '+str(i+1)+' Accuracy: '+str(ac))
    writer.writerow(['Accuracy='+str(ac), 'Test size='+str(tot_test)])
printPreOrder(root)

g_acc=(g_r_tol/g_tot)*100
msg='\nAccuracy: '+str(g_acc)+'%\n'+'Total testset size: '+str(g_tot)+'\nCheck '+saveFileName+' for details'
print(msg)


writer.writerow(['Decision Tree Grand Accuracy='+str(g_acc)+'%', 'Total Tests:'+str(g_tot)])
writer.writerow([])
easygui.msgbox(msg, 'Testing Complete')
outputFile.close()
file.close()