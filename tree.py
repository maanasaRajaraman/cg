# -*- coding: utf-8 -*-
"""
Created on Fri Apr 12 18:41:33 2024

@author: maana
"""

import turtle

MINIMUM_LENGTH = 5

def build_tree(t,angle,length,shorten_by):
    if length > MINIMUM_LENGTH:
        t.forward(length)
        nlength = length - shorten_by
        t.left(angle)
        build_tree(t, angle, nlength, shorten_by)

        t.right(angle*2)
        build_tree(t, angle, nlength, shorten_by)

        t.left(angle)
        t.backward(length)
    return


tree = turtle.Turtle()
tree.hideturtle()
tree.setheading(90)
tree.color('green')

build_tree(tree, 30,50, 5)
turtle.mainloop()
