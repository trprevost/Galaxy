from galaxy import *
import copy
import time
import pygame
import math

earth = Body(800,150,20,0,10,0,0,10)
venus = Body(800,600,-19,0,5,0,0,10)
sun = Body(800,450,0,0,300,0,0,30)
trace = []

listePlanet = [earth, venus]
listeSun = [sun]

def isPulled(b1,b2):
    x1 = b1.pos.x
    x2 = b2.pos.x
    y1 = b1.pos.y
    y2 = b2.pos.y
    dist = math.sqrt((x1-x2)**2 + (y1-y2)**2)
    acc = (b1.mass+b2.mass)/(dist**2)
    b1.acc = Vec2((x2-x1)*acc, (y2-y1)*acc)


def update(listePlanet,listeSun):
    for i in range (0, len(listePlanet)):
        for j in range(0, len(listeSun)):
            isPulled(listePlanet[i], listeSun[j])
            #isPulled(liste[j], liste[i])


    for g in listePlanet+listeSun:
        x = g.pos.x
        y = g.pos.y
        trace.append((x,y))
        g.move()
        x = g.pos.x
        y = g.pos.y
    
        if(x < 1600 and y < 900 ):
            pygame.draw.circle(screen, white, (x,y), g.radius, width=0)

    for i in trace:
        pygame.draw.circle(screen, white, i, 1, width=0)


white=(255,255,255)
pygame.init()
screen = pygame.display.set_mode((1600,900))

launched = True
while launched:
    pygame.display.flip()
    screen.fill((0,0,0))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            launched = False
    update(listePlanet, listeSun)
    time.sleep(0.01)


