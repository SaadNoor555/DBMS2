import numpy as NP
from PIL import Image
from pathlib import Path
from time import time
import math

def calcDistance(pix1, pix2):
    return math.sqrt((pix1[0]-pix2[0])**2 + (pix1[1]-pix2[1])**2 + (pix1[2]-pix2[2])**2)

def countImgDistance(files, type):
    for file in files:
        img = Image.open(file)
        img.resize((x, y))
        dis = 0
        for (pix1, pix2) in zip(testImg.getdata(), img.getdata()):
            dis += calcDistance(pix1, pix2)
        distance.append([dis, type])

K = 3
start_time = time()
x, y= 500, 500
folders = ['winter', 'summer']
testImg = Image.open('w-2.jpg')
testImg.resize((x, y))

distance = list()
for folder in folders:
    countImgDistance(Path(folder).glob('*'), folder)

distance.sort(key = lambda x: x[0])

mp = {}
for type in folders:
    mp[type] = 0

for i in range(K): mp[distance[i][1]]+=1

sortedDict = {k:v for k, v in sorted(mp.items(), reverse=True, key=lambda x: x[1])}
print(sortedDict)
for key in sortedDict:
    print(key)
    break

print("--- %s seconds ---" % (time() - start_time))