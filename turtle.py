import turtle

from PIL import Image



screen = turtle.Screen()

screen.bgcolor("white")



pen = turtle.Turtle()



for _ in range(4):

    pen.forward(100)

    pen.right(90)



pen.penup()

pen.forward(100)

pen.pendown()

 

pen.color('yellow')

pen.circle(50)



pen.penup()

pen.goto(150, 0)

pen.pendown()



pen.color('red')

pen.begin_fill()

pen.circle(40)

pen.end_fill()



pen.penup()

pen.goto(300, 0)

pen.pendown()



for _ in range(3):

    pen.forward(100)

    pen.left(120)

    

fileName = "imageGrab.png"



#turtle.getscreen().getcanvas().postscript(file='outputname.ps')







turtle.mainloop()

turtle.getscreen().getcanvas().postscript(file='outputname.ps')

img=Image.open('outputname.ps')

print(img)
