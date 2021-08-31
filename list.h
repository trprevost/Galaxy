#ifndef LIST
#define LIST
#include "body.h"

typedef struct listBody{
    Body * body;
    struct listBody * next;
}listBody;

void addList(Body * b, listBody ** list);

#endif

