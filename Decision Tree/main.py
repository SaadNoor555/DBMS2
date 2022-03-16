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
    title = "Enter File Name"
    text = "Result File Name:"
    d_text = "*.csv"
    saveFileName = easygui.enterbox(text, title, d_text)
    if saveFileName.endswith('.csv')==False:
        saveFileName += '.csv'
    outputFile = open(saveFileName, 'w', newline='')
    writer = csv.writer(outputFile)
    writer.writerow(['expected', 'found', 'correctness'])
    r_ans, tot_test= 0, 0
    for row in testset:
        cls= findAppropriateNode(root, row)
        writer.writerow([row[0], cls, cls == row[0]])
        if cls == row[0]:
            r_ans+=1
        tot_test+=1
    ac = (r_ans/tot_test)*100
    writer.writerow(['Accuracy='+str(ac)])
    msg='Accuracy: '+str(ac)+'%\n'+'Sample testset size: '+str(tot_test)+'\nCheck '+saveFileName+' for details'
    easygui.msgbox(msg, 'Testing Complete')
    outputFile.close()

def seperateDataset(dataset):
    testset,trainSet=[],[]
    for row in dataset:
        if random.random()>0.8:
            testset.append(row)
        else:
            trainSet.append(row)
    return trainSet, testset

def printPreOrder(node, depth):
    if node.leftChild!=None:
        printPreOrder(node.leftChild, depth+1)
    if node.rightChild!=None:
        printPreOrder(node.rightChild, depth+1)
    for i in range(depth): print(end=' ')
    print(node.dim, ', ', node.val)

'''driver starts here'''
file = open(CON.getFile())
csvreader = csv.reader(file)
dataset = []
for row in csvreader:
    dataset.append(row)

title = "Create Decision Tree"
text = "Enter number of class:"
n_class = int(easygui.enterbox(text, title))
trainSet, testset= seperateDataset(dataset)
root = DT.build_decision_tree(trainSet, n_class)
printPreOrder(root,0)
testDecisionTree(root, testset)
file.close()

