#include "physics.h"

float coeff = 0.5; 

void move(Body * me){
    me->speed->x += me->acc->x;
    me->speed->y += me->acc->y;

    me->pos->x += me->speed->x;
    me->pos->y += me->speed->y;

    me->acc->x = 0;
    me->acc->y = 0;
}

void isPulledSP(Body * planet, Body * star){
    int x1 = planet->pos->x;
    int y1 = planet->pos->y;
    int x2 = star->pos->x;
    int y2 = star->pos->y;

    double distance = pow((x1-x2),2.0) + pow((y1-y2), 2.0);
    double acceleration = (planet->mass + star->mass) / distance ;
    if (distance >10000)
    {
        acceleration /= distance/10000;
    }
    planet->acc->x += acceleration * (x2-x1);
    planet->acc->y += acceleration * (y2-y1);
    star->acc->x += acceleration * (x1-x2) * 0.01;
    star->acc->y += acceleration * (y1-y2) * 0.01;
    
            

}

void isPulled(Body * planet, Body * star){

    int x1 = (int)planet->pos->x;
    int y1 = (int)planet->pos->y;
    int x2 = (int)star->pos->x;
    int y2 = (int)star->pos->y;


    double distance = pow((x1-x2),2.0) + pow((y1-y2), 2.0);
    double acceleration = (planet->mass + star->mass) / distance;
    if (distance >1000000)
    {
        acceleration /= distance/10000;
    }
    planet->acc->x += acceleration * (x2-x1) * coeff / planet->mass;
    planet->acc->y += acceleration * (y2-y1) * coeff / planet->mass;
    star->acc->x += acceleration * (x1-x2) * coeff /star->mass;
    star->acc->y += acceleration * (y1-y2) * coeff /star->mass;
            //printf("accx: %f    accy: %f", planet->acc->x, planet->acc->y);

}

void isPulledStar(Body * planet, Body * star){
    int x1 = planet->pos->x;
    int y1 = planet->pos->y;
    int x2 = star->pos->x;
    int y2 = star->pos->y;

    double distance = pow((x1-x2),2.0) + pow((y1-y2), 2.0);
    double acceleration = (planet->mass + star->mass) / distance;
    if (distance >100000)
    {
        acceleration/= distance/100000;
    }
    planet->acc->x += acceleration * (x2-x1) * coeff / (planet->mass/100);
    planet->acc->y += acceleration * (y2-y1) * coeff / (planet->mass/100);
    star->acc->x += acceleration * (x1-x2) * coeff /(planet->mass/100);
    star->acc->y += acceleration * (y1-y2) * coeff /(planet->mass/100);
    
            

}