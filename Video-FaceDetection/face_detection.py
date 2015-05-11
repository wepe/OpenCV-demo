#-*-coding:utf8-*-#
"""
@Created on 2015/05/10
@author: wepon 
@coed: https://github.com/wepe
@file:face_detection.py

"""
import cv2

def detectFaces(img):
    #if you use this code,change the path of "haarcascade_frontalface_default.xml" to yours
    face_cascade = cv2.CascadeClassifier("/home/wepon/OpenCV-demo/opencv-data/haarcascades/haarcascade_frontalface_default.xml")
    if img.ndim == 3:
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    else:
        gray = img 
    faces = face_cascade.detectMultiScale(gray, 1.2, 5)
    result = []
    for (x,y,width,height) in faces:
        result.append((x,y,x+width,y+height))
    return result


def drawFaces(img):
    faces = detectFaces(img)
    if faces: 
        for (x1,y1,x2,y2) in faces:
            cv2.rectangle(img,(x1,y1),(x2,y2),(225,105,65),3)
            font = cv2.FONT_HERSHEY_SIMPLEX
            cv2.putText(img,'FaceDetection',(x1,y1-5), font, 1,(255,0,255),2)          
    return img
