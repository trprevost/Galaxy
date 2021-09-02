#include "calculs.h"
#include "omp.h"
#include "physics.h"
#include<stdlib.h>
#include<stdio.h>

extern struct Body* tabPlanets[500];
extern struct Body* tabStars[100];
extern int nbPlanets;
extern int nbStars;


/**
 * refresh the position of all planets ans stars
 **/
void refreshPosition(){
   
    for (int i = 0; i < nbStars; i++)
    {
        move(tabStars[i]);
    }
    for (int i = 0; i < nbPlanets; i++)
    {
        move(tabPlanets[i]);
    }
    
}


/**
 * refresh the acceleration of all planets and stars
 **/
void refreshList(){

// for all planet, each star
#pragma omp parallel 
#pragma omp for schedule(static,2) 
    for (int i = 0; i < nbPlanets; i++)
    {
        for (int j = 0; j < nbStars; j++)
        {
            isPulled(tabPlanets[i], tabStars[j]); 
        }
        
    }
    

//for all planet, each planet  
int i;
#pragma omp parallel 
#pragma omp for schedule(dynamic) //collapse (2)
    for (i = 0; i < nbPlanets-1; i++)
    {
        for (int j = i+1; j < nbPlanets; j++)
        {
            isPulled(tabPlanets[i],tabPlanets[j]);
        }
        
    }
    
//for all stars, each star
#pragma omp parallel 
#pragma omp for schedule(static,2)
    for (int i = 0; i < nbStars-1; i++)
    {
        for (int j = i+1; j < nbStars; j++)
        {
            isPulledStar(tabStars[i], tabStars[j]);

        }
        
    }
    


}