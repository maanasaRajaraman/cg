from turtle import *
color('red')
rule=['f','x']
prev=['f','x']
ans=[]
xVals = ['x','+','y','f','+']
yVals = ['-','f','x','-','y']

for iter in range(7):
    ans = []
    for i in prev:
        if(i=='x'):
            ans+=xVals
        elif(i=='y'):
            ans+=yVals
        else:
            ans.append(i)
    prev = ans

#print(ans)

for i in range(0,len(ans)):
    if(ans[i] == '+'):
        right(90)
    elif(ans[i] == '-'):
        left(90)
    elif(ans[i] == 'f'):
        forward(20)

done()

