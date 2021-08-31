from vec2 import *

class Body:
    pos = None
    speed = None
    acc = None

    radius = None

    mass = None

    def __init__(self, myx, myy, speedx, speedy, myMass, accy, accx, rad):
        self.pos = Vec2(myx,myy)

        self.speed = Vec2(speedx,speedy)

        self.acc = Vec2(accx, accy)

        self.radius = rad
        self.mass = myMass

    def move(self):
        self.speed.plus(self.acc)
        self.pos.plus(self.speed)
        self.acc.x = 0
        self.acc.y = 0