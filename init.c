//#include "init.h"
#include "init.h"
#include <stdio.h>


    //stars
    Color white = {255,255,255};
    Color lightOrange = {255,147,51};
    Color darkOrange = {255,87,51};
    Color lightBlue = {144,218,253};
    Color yellow = {235,227,56};
    Color lightYellow = {237,232,134};
    Color red = {240,27,27};

    //planets 
    Color blue = {51,156,255};
    Color darkBlue = {50,50,200};
    Color green = {62,221,42};
    Color lightGreen = {170,255,170};
    Color darkGreen = {37,158,22};
    Color purple = {169,27,240};
    Color turquoise = {51,219,255};
    Color orange = {255,207,28};

float distance(int x1, int y1, int x2, int y2 ){
    return pow((x1-x2),2.0) + pow((y1-y2), 2.0);
}

// check if distance² betweens the new star and others is more than 3 000 000
int checkSun(listBody** stars, Body * b){
    int x = (int)b->pos->x;
    int y = (int)b->pos->y;
    int x2, y2;

    listBody *tmp = *stars;

    while (tmp != NULL)
    {
        x2 = (int)tmp->body->pos->x;
        y2 = (int)tmp->body->pos->y;

        if (distance(x,y,x2,y2)<3000000)
        {
            free(b);
            return 0;
        }

        tmp = tmp->next;

    }

    return 1;
}

Color StarColor(int r){
    switch (r)
    {
    case 0:
        return white;
    case 1:
        return lightOrange;
    case 2:
        return darkOrange;
    case 3:
        return lightBlue;
    case 4:
        return lightYellow;
    case 5:
        return yellow;
    case 6:
        return red;
    
    default:
        return white;
    }
}

Color PlanetColor(int r){
    switch (r)
    {
    case 0:
        return turquoise;
    case 1:
        return blue;
    case 2:
        return darkBlue;
    case 3:
        return green;
    case 4:
        return lightGreen;
    case 5:
        return darkGreen;
    case 6:
        return purple;
    case 7:
        return red;
    case 8:
        return orange;
    
    default:
        return red;
    }
}

Body * addPlanet(int x, int y){




    
    Body* b = malloc(sizeof(Body));
    b->pos = malloc(sizeof(Vec2));
    b->speed = malloc(sizeof(Vec2));
    b->acc = malloc(sizeof(Vec2));

    b->pos->x = x;b->pos->y = rand()%400+y+150;
    b->acc->x=0;b->acc->y=0;
    
    int distance = sqrt (pow((x-b->pos->x),2.0) + pow((y-b->pos->y), 2.0));
    b->mass = 5;

    //clock direction or anti clock direction
    int direction = rand();
    direction = (direction%2 == 0)?1:-1;
    b->speed->x= rand()%3+15;
    //b->speed->x *= direction;

    b->speed->y=0;
    b->radius = 7;

    int random = rand()%9;
    b->color =PlanetColor(random);
    
    return b;
}

Body * addStar(){
    

    Body* b = malloc(sizeof(Body));
    b->pos = malloc(sizeof(Vec2));
    b->speed = malloc(sizeof(Vec2));
    b->acc = malloc(sizeof(Vec2));

    b->pos->x = rand()%9822; 
    b->pos->y = rand()%5400;
    b->acc->x=0;b->acc->y=0;
    
    b->mass = 3000;

    
    b->speed->y=0; b->speed->x=0;
    b->radius = 30;

    int random = rand()%7;
    b->color =StarColor(random);

    return b;
}


void printL(listBody ** l){
    listBody * tmp = *l;
 while (tmp != NULL)
    {
        printf("%d\n", tmp->body->mass);
        tmp = tmp->next;
    }

}
void addSolarSystem(listBody** stars, listBody** planets){
    int static firstTime = 1;
    int wellPlaced = 0;
    Body *sun ;
    int i = 0;
    if(firstTime){
        srand(time(NULL)); // random initialization, should only be called once.
        sun = addStar();
    }


    //printf("wp: %d,  firstime: %d \n", wellPlaced, firstTime);
    while (!wellPlaced && i<50 && !firstTime)
    {
        sun = addStar();

        wellPlaced = checkSun(stars, sun);

        i++;
        if (i == 50 && wellPlaced == 0)
        {
            sun = addStar();
        }
        
    }
    

    

    int nbPlanets = rand()%4+4;
    for (int i = 0; i < nbPlanets; i++)
    {
        addList(addPlanet((int)sun->pos->x, (int)sun->pos->y), planets);


    }
    

    addList(sun, stars);

    if (firstTime)
    {
        (*stars)= (*stars)->next;
        (*planets) = (*planets)->next;
        firstTime = 0;
    }

}