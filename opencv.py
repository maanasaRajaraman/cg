# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 19:05:25 2024

@author: maana
"""


import cv2
import numpy as np
import matplotlib.pyplot as plt

#reading path
img = cv2.imread('p1.jpg')
print(img)

#show resized image
img1 = cv2.resize (img, (400, 400))
cv2.imshow("cv", img1)
cv2.waitKey(0)


#gray scaled picture
gray_img = cv2.cvtColor (img1, cv2.COLOR_BGR2GRAY)
cv2.imshow("cv",gray_img)
cv2.waitKey(0)

#flip image
flip_img = cv2.flip(img1, 0)
cv2.imshow("cv",flip_img)
cv2.waitKey(0)

#inverting image
invert_img = cv2.bitwise_not(img1)
cv2.imshow("cv",invert_img)
cv2.waitKey(0)

#blurring an image
blur_img = cv2.blur(img1, (5,5))
cv2.imshow("cv",invert_img)
cv2.waitKey(0)

#dilation, erodation
dia_img = cv2.dilate(img1, np.ones((5,5)))
eroded_img = cv2.erode(img1, np.ones((5, 5)))
cv2.imshow("cv",dia_img)
cv2.imshow("cv",eroded_img)
cv2.waitKey(0)

#thresholding
var, threshold = cv2.threshold(gray_img, 100, 100, cv2.THRESH_BINARY)
cv2.imshow("cv",threshold)
cv2.waitKey(0)

#edge detection
img_edge = cv2.Canny(img1, 100, 100)
cv2.imshow("cv",img_edge)
cv2.waitKey(0)

#--------------------------------------------------

#adaptive thresholds

#show resized image
img1 = cv2.resize (img, (400, 400))
cv2.imshow("cv", img1)
cv2.waitKey(0)

img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)

th1 = cv2.adaptiveThreshold(img1, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 7, 4)
th2 = cv2.adaptiveThreshold(img1, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 7, 4)
# display the images
#cv2.imshow("cv",th1)
#cv2.imshow("cv",th2)


val, th1 = cv2.threshold(img1, 110, 255, cv2.THRESH_BINARY)
val, th2 = cv2.threshold(img1, 110, 255, cv2.THRESH_BINARY_INV)
val, th3 = cv2.threshold(img1, 110, 255, cv2.THRESH_TRUNC)
val, th4 = cv2.threshold(img1, 110, 255, cv2.THRESH_TOZERO)
val, th5 = cv2.threshold(img1, 110, 255, cv2.THRESH_TOZERO_INV)

cv2.imshow("THRESH_BINARY",th1)
cv2.waitKey(0)
cv2.imshow("THRESH_BINARY_INV",th2)
cv2.waitKey(0)
cv2.imshow("THRESH_TRUNC",th3)
cv2.waitKey(0)
cv2.imshow("THRESH_TOZERO",th4)
cv2.waitKey(0)
cv2.imshow("THRESH_TOZERO_INV",th5)
cv2.waitKey(0)

#----------------------------------------
#blurring , smoothening , gradients, contours

#reading path
img = cv2.imread('p1.jpg')
#print(img)

#show resized image
img1 = cv2.resize (img, (400, 400))
#cv2.imshow("cv",img1)

gray_img = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)

blur_img = cv2.blur(img1,(3,3))
cv2.imshow("blur",blur_img)
cv2.waitKey(0)

#gaussian blur
gaus_img = cv2.GaussianBlur(img1, (5,5), 2)
cv2.imshow("gaussian blur",gaus_img)
cv2.waitKey(0)

#median blur
median_blur = cv2.medianBlur(img1, 3)
cv2.imshow("median blur",median_blur)
cv2.waitKey(0)

#Bilateral Filter
bilateral_img = cv2.bilateralFilter(img1, 7, 100, 100)
cv2.imshow("Bilateral Filter",bilateral_img)
cv2.waitKey(0)

#laplacian, sobel gradient
lap = np.uint8(np.absolute(cv2.Laplacian(img1, cv2.CV_64F, ksize=1)))
vertical = np.uint8(np.absolute(cv2.Sobel(img1, cv2.CV_64F, 1,0, ksize=1)))
horizon = np.uint8(np.absolute(cv2.Sobel(img1, cv2.CV_64F, 0,1, ksize=1)))
Sobel = cv2.bitwise_or(vertical, horizon)

cv2.imshow("Laplacian",lap)
cv2.waitKey(0)

cv2.imshow("Sobel",Sobel)
cv2.waitKey(0)

#contours
'''
val, th1 = cv2.threshold(img1, 110, 255, cv2.THRESH_BINARY)
contours,_ = cv2.findContours(th1, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
cv2.drawContours(img1, contours, -1, (0,0,255),1)
cv2.imshow("cv",img1)
cv2.waitKey(0)
'''
#-------------------------------

#translation, rotation

img = cv2.imread('p2.jpg')
img1 = cv2.resize (img, (500, 300))
cv2.imshow("cv", img1)

img = cv2.imread('p2.jpg', cv2.IMREAD_GRAYSCALE)
img = cv2.resize (img, (500, 300))
rows,cols = img.shape
 
M1 = np.float32([[1,0,100],[0,1,50]])
transf_img = cv2.warpAffine(img, M1, (cols,rows))
 
M2 = cv2.getRotationMatrix2D(((cols-1)/2.0,(rows-1)/2.0),90,1)
rot_img = cv2.warpAffine(img, M2, (cols,rows))

cv2.imshow("transformed img ",transf_img)
cv2.waitKey(0)

cv2.imshow("roated img",rot_img)
cv2.waitKey(0)

#affine tranformation

p1 = np.float32([[50, 50], [200, 50], [50, 200]])
p2 = np.float32([[10,100],[200,50],[100,250]])

M3 = cv2.getAffineTransform(p1, p2)
 
dst = cv2.warpAffine(img, M3, (cols,rows))
 
plt.subplot(121),plt.imshow(img),plt.title('Input')
plt.subplot(122),plt.imshow(dst),plt.title('Output')
plt.show()

#-----------------
#2D convolution filtering

img = cv2.imread('p2.jpg')
img = cv2.resize (img, (500, 300))

kernel = np.ones((5,5), np.float32)/25
conv_img = cv2.filter2D(img, -1, kernel)
blur = cv2.blur(img,(5,5))

cv2.imshow("cv", img)
cv2.imshow("convolution", conv_img)
cv2.imshow("Average Blur", blur)
cv2.waitKey(0)