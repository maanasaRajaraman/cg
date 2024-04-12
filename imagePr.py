# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 20:18:14 2024

@author: maana
"""

import cv2
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.image as mpimg
from skimage.exposure import match_histograms
from PIL import Image
from numpy import asarray

def sobel(image):
    grayImage = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    cv2.imshow('Gray Image',grayImage)
    cv2.waitKey(0)
    image_blur = cv2.GaussianBlur(grayImage,(3,3),0)
    after_sobel_image = cv2.Sobel(src=image_blur,ddepth = cv2.CV_64F,dx=1,dy=0,ksize=5)
    cv2.imshow('Sobel Image',after_sobel_image)
    cv2.waitKey(0)


def canny_filter(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    image_blur = cv2.GaussianBlur(gray,(3,3),0)
    canny_img = cv2.Canny(image_blur,100,200)
    cv2.imshow('Canny image',canny_img)
    cv2.waitKey(0)

def histogram(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    hist = cv2.calcHist(gray,[0],None,[256],[0,256])
    plt.hist(gray.ravel(),256,[0,256])
    plt.show()

def histEq(image):
    cv2.imshow('Gray Scale Image', image)
    cv2.waitKey(0)
    equalized = cv2.equalizeHist(image)
    cv2.imwrite('equalized.jpg', equalized)
    eqImage = cv2.imread('equalized.jpg',0)
    hist = cv2.calcHist(eqImage, [0], None,[256], [0,256])
    plt.plot(hist)
    plt.show()
    equalizedImage = cv2.imread('equalized.jpg')
    cv2.imshow('Equalized Image',equalizedImage)
    cv2.waitKey(0)

def blackAndWhite(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.imshow('img',gray)
    (threshold,binary) = cv2.threshold(gray,125,255,cv2.THRESH_BINARY)
    cv2.imwrite('bgimage.jpg',binary)
    bn = cv2.imread('bgimage.jpg')
    img = cv2.imshow('black and white',bn)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# Low pass and high pass are frequency filters
def lowPass(image):
    kernel = np.array([[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1],[1,1,1,1,1]])
    img = cv2.filter2D(image,-1,kernel/sum(kernel))
    cv2.imshow('Low pass Image',img)
    cv2.waitKey(0)

def highPass(image):
    kernel = np.array([[0,-1,0],[-1,5,-1],[0,-1,0]])
    img = cv2.filter2D(image,-1,kernel)
    cv2.imshow('High Pass',img)
    cv2.waitKey(0)

def matched_histograms(image):
    ref = cv2.imread('p2.jpg')
    matched = match_histograms(image,ref)
    fig, (ax1, ax2, ax3) = plt.subplots(ncols=3, figsize=(8, 2.5))

    ax1.imshow(image, cmap=plt.cm.gray)
    ax1.set_title('Input image')

    ax2.imshow(ref, cmap=plt.cm.gray)
    ax2.set_title('Reference image')

    ax3.imshow(matched, cmap=plt.cm.gray)
    ax3.set_title('Matched image')

    for ax in (ax1, ax2, ax3):
        ax.axis('off')

    plt.show()

def neg_imag():
    img = Image.open('p2.jpg')
    data = asarray(img)
    data = abs(255 - 1 - data)
    image = Image.fromarray(data)
    image.save('NegativeTiger.jpg')

#These are spatial filters

def mean(image):
    mean_image = cv2.blur(image,(3,3))
    cv2.imshow('Mean filtered',mean_image)
    cv2.waitKey(0)

def median(image):
    median_image = cv2.medianBlur(image,5)
    cv2.imshow('Median Blur',median_image)
    cv2.waitKey(0)

def sharpening(image):
    kernel= np.array([[-1,-1,-1],[-1,9,-1],[-1,-1,-1]])
    sharpened_image =cv2.filter2D(image,-1,kernel)
    cv2.imshow('Sharpened Image',sharpened_image)
    cv2.waitKey(0)

def erosion(image):
    kernel=np.ones((5,5),np.uint8)
    eroded_image = cv2.erode(image,kernel,iterations=1)
    cv2.imshow('Eroded Image',eroded_image)
    cv2.waitKey(0)

def dilation(image):
    kernel =np.ones((5,5),np.uint8)
    dilated_image=cv2.dilate(image,kernel,iterations=1)
    cv2.imshow('Dilated Image',dilated_image)
    cv2.waitKey(0)

def opening(image):
    kernel =np.ones((5,5),np.uint8)
    opening_image=cv2.morphologyEx(image,cv2.MORPH_OPEN,kernel,iterations=1)
    cv2.imshow('Opening Image',opening_image)
    cv2.waitKey(0)

def closing(image):
    kernel=np.ones((5,5),np.uint8)
    closing_image=cv2.morphologyEx(image,cv2.MORPH_CLOSE,kernel,iterations=1)
    cv2.imshow('Closing Image',closing_image)
    cv2.waitKey(0)

def hitMiss(image):
    kernel=np.array(([1,1,1],[0,1,-1],[0,1,-1]),dtype = "int")
    grayImage=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
    hitMissImage=cv2.morphologyEx(grayImage,cv2.MORPH_HITMISS,kernel,iterations=1)
    cv2.imshow('Hit Miss Image',hitMissImage)
    cv2.waitKey(0)


image = cv2.imread('p1.jpg')
blackAndWhite(image)