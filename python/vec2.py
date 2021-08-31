class Vec2:

    x = None
    y = None

    def __init__ (self, myx, myy):
        self.x = myx
        self.y = myy

    def minus(self,v):
        self.x -= v.x
        self.y -= v.y

    def plus(self,v):
        self.x += 0.2*v.x
        self.y += 0.2*v.y