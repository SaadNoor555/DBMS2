from fileinput import filename
import numpy as NP
from PIL import Image
import os
from pathlib import Path

directory1= "G:\Study\5th Sem\DBMS\Codes\DBMS2\Mask"
directory= "G:\Study\5th Sem\DBMS\Codes\DBMS2\images"
# files= Path(directory).glob('*')
files1= Path(directory1).glob('*')

cnt= NP.zeros([256,256,256])
nskin = NP.zeros([256,256,256])
proSkin=NP.zeros([256,256,256])

# im= Image.open("G:\Study\5th Sem\DBMS\Codes\DBMS2\Mask\0000.bmp")
# filename= im.info["filename"]
# newf= filename[0:-3]
# newf= newf+ "jpg"

for im2 in files1:
    # print("hello")

    im = Image.open(im2)
    filename= im.info["filename"]
    newf= filename[0:-3]
    newf= newf+ "jpg"
    ims= Image.open(directory+ "/"+newf)

    for (pixel, pixel1) in im.getdata():
        if pixel[0]<200 or pixel[1]<200 or pixel[2]<200:
            print("hello")
            cnt[pixel1[0]][pixel1[1]][pixel1[2]]+=1
        else:
            nskin[pixel1[0]][pixel1[1]][pixel1[2]]+=1
            print("hi")
    

for r in range(0,256):
    for g in range(0,256):
        for b in range(0,256):
            if(cnt[r][g][b]+nskin[r][g][b]!=0):
                proSkin[r][g][b]= cnt[r][g][b]/(cnt[r][g][b]+nskin[r][g][b])

for r in range(0,256):
    for g in range(0,256):
        for b in range(0,256):
            if(nskin[r][g][b]!=0):
                print(r, g, b)

tc= 0.3

im1= Image.open('0003.jpg')
wid,hig= im1.size
# print(wid)
# print(hig)

o_img = Image.new(mode="RGB", size=im1.size)
pixel_map = o_img.load()



for x in range (0, wid):
    for y in range (0, hig):
        pix = im1.getpixel((x,y))
        if(proSkin[pix[0]][pix[1]][pix[2]]<tc):
            pixel_map[x,y]= 0,0,0
        else:
            pixel_map[x,y]= 255,255,255
# print(cnt)

o_img.save('r3.jpg')
o_img.show()
