# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 17:42:04 2024

@author: maana
"""

from turtle import *
color('red')

rule=['r','f','l','l','f','r']
prev=['r','f','l','l','f','r']
ans=[]
for iter in range(4):
    ans = []
    for i in prev:
        if(i=='f'):
            ans+=rule
        else:
            ans.append(i)
    prev = ans

print(ans)

for i in range(0,len(ans)):
    if(ans[i] == 'r'):
        right(45)
    elif(ans[i] == 'f'):
        forward(20)
    elif(ans[i] == 'l'):
        left(45)


done()