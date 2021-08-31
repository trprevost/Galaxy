#include "calculs.h"
#include "omp.h"
#include "physics.h"
#include<stdlib.h>
#include<stdio.h>

void refreshPosition(listBody ** planet){
    listBody * tmp = *planet;
    
    if (tmp == NULL)
    {
         printf("erreur refresh Position\n");
    }
    while (tmp != NULL)
    {
        move(tmp->body);
        tmp = tmp->next;
    }
}

void refreshList(listBody ** planet, listBody **stars){
    
    listBody * tmp = *planet;
    listBody * tmp2 = (*planet)->next;
    listBody * tmpStars = *stars;
    listBody * tmpStars2 = (*stars)->next;
    if (tmp == NULL)
    {
         printf("erreur refresh list\n");
    }

// for all planet, each star
    while (tmp != NULL)
    {
        
        #pragma omp parallel
        #pragma omp single
        #pragma omp task untied
        while (tmpStars != NULL)
        {
            //isPulledSP(tmp->body, (tmpStars)->body);
            #pragma omp task firstprivate(tmp, tmpStars)
            {
            isPulled(tmp->body, (tmpStars)->body);
            //printf("fait par %d   position %f   position %f\n", omp_get_thread_num(), tmp->body->pos->y,tmpStars->body->pos->y );
            }
            tmpStars = tmpStars->next;
            
        }
        
        tmpStars = *stars;
        tmp = tmp->next;
    }
    tmp = *planet;

//for all planet, each planet
    while (tmp->next != NULL)
    {

        while (tmp2 != NULL)
        {
            //isPulledPlanet(tmp->body, tmp2->body);
            isPulled(tmp->body, tmp2->body);
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
        tmp2 = tmp->next;
    }
    tmpStars = *stars;
    
//for all stars, each star
    while (tmpStars->next != NULL)
    {

        while (tmpStars2 != NULL)
        {
            //isPulledStar(tmpStars->body, tmpStars2->body);
            isPulledStar(tmpStars->body, tmpStars2->body);
            tmpStars2 = tmpStars2->next;
        }
        tmpStars = tmpStars->next;
        tmpStars2 = tmpStars->next;
    }


}