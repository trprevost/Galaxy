#include "list.h"
#include <stdio.h>
#include <stdlib.h>


void addList(Body * b, listBody ** list){

    listBody * new = malloc(sizeof(listBody));
    new->body = b;
    new->next = NULL;
    listBody * tmp = *list;
    //printf("new%d\n", new->body->mass);
    
    //        printf("b: %d\n", b->mass);



    while(tmp->next != NULL)
        tmp = tmp-> next;

    tmp->next = new;
    //printf("tmp next%d\n", tmp->next->body->mass);

}