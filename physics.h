#ifndef PHY
#define PHY
#include "list.h"
#include <math.h>


void move(Body * me);

void isPulledSP(Body * planet, Body * star);

void isPulled(Body * planet, Body * star);

void isPulledStar(Body * planet, Body * star);

#endif