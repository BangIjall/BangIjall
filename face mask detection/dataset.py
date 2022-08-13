import cv2
#import numpy as np
import os
#import subprocess
import urllib3

faceDetect = cv2.CascadeClassifier('mask8.xml')
faceDetectfrontal = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cam = cv2.VideoCapture(0)
http = urllib3.PoolManager()
id = input('Masukan Nama: ')
directory = str(id)
parent_dir = "C:/Users/HP/Documents/projek/Joki/BangIjall/face mask detection/dataset/"
path = os.path.join(parent_dir, directory) 
os.mkdir(path)
sampleNum=0
kondisi=0
#def training():
#    subprocess.call(["python", "encode_faces.py"])
    
while(True):
    ret,img = cam.read()
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    if(kondisi==0):
        faces = faceDetectfrontal.detectMultiScale(gray,1.3,5)
        for(x,y,w,h) in faces:

            sampleNum=sampleNum+1
            cv2.imwrite("dataset/"+str(id)+"/"+str(sampleNum)+".jpg",img[y:y+h,x:x+w])
            cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
            cv2.waitKey(100)

        cv2.imshow("Face",img)
        cv2.waitKey(1)
        if(sampleNum>20):
            kondisi=1
    elif(kondisi==1):
        print("Sekarang pakai masker: ")
        choice=input("Mulai Y/N?")
        if(choice=="Y"):
            kondisi=2
    elif(kondisi==2):
        faces = faceDetect.detectMultiScale(gray, 1.3, 5)
        for (x, y, w, h) in faces:
            sampleNum = sampleNum + 1
            cv2.imwrite("dataset/" + str(id) + "/" + str(sampleNum) + ".jpg", img[y:y + h, x:x + w])
            cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.waitKey(100)

        cv2.imshow("Face", img)
        cv2.waitKey(1)
        if (sampleNum > 40):
            break

cam.release()
cv2.destroyAllWindows()
