#ifndef MAIN
#define MAIN

#include <SDL2/SDL.h>
#include <stdio.h>
#include "graphics.h"
#include "physics.h"
#include "init.h"
#include "omp.h"



/*Color white1 = {255,255,255};
    Color darkOrange1 = {255,87,51};
    Color lightOrange1 = {255,147,51};
    Color turquoise1 = {51,219,255};
    Color blue1 = {51,156,255};
    Color darkBlue1 = {7,4,147};
    Color lightBlue1 = {144,218,253};
    Color yellow1 = {235,227,56};
    Color lightYellow1 = {237,232,134};
    Color green1 = {62,221,42};
    Color lightGreen1 = {141,238,130};
    Color darkGreen1 = {37,158,22};
    Color red1 = {240,27,27};
    Color purple1 = {169,27,240};*/



int x_shift = 0;
int y_shift = 0;
int static x_size = 1600;
int static y_size = 900;
int pixel_step = 5;
float zoom = 1;
float step_zoom = 0.25;
int pause = 0;

//gcc *.c -lm $(sdl2-config --cflags --libs -ldl ) && ./a.out
// GLOBAL
SDL_Window * window = NULL;
SDL_Renderer *renderer = NULL;
void SDL_EXIT()
{
    SDL_Log("ERREUR : Initialisation > %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
    SDL_Quit();
}

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
        #pragma omp master
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

int keys(int * isRunning)
{
    SDL_Event ev;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        int up = keystates[SDL_SCANCODE_UP];
        int down = keystates[SDL_SCANCODE_DOWN];
        int left = keystates[SDL_SCANCODE_LEFT];
        int right = keystates[SDL_SCANCODE_RIGHT];
        int escape = keystates[SDL_SCANCODE_ESCAPE];
        int minus = keystates[SDL_SCANCODE_KP_MINUS];
        int plus = keystates[SDL_SCANCODE_KP_PLUS];
        //e = keystates[SDL_SCANCODE_E]
        int p = keystates[SDL_SCANCODE_P];

        if (escape){
                *isRunning = 0;
        }
        
        if (up && y_shift < 1000/*&& y_shift > pixel_step*/){
            y_shift += pixel_step *2;
        }
        if (down ){
            y_shift -= pixel_step *2;
        }
        if (right /*&& x_shift > pixel_step*/){
            x_shift -= pixel_step *2;
        }
        if (left && x_shift < 1000){
            x_shift += pixel_step *2;
        }
       
        
        
        
        

        while(SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                *isRunning = 0;
            }
            if(ev.type == SDL_KEYDOWN)
            {
                switch(ev.key.keysym.sym)
                {
                    case SDLK_KP_PLUS:
                        if (zoom < 8 )
                        {
                            float xdiff = zoom * x_size - (zoom + step_zoom) * x_size;
                            xdiff = (int)(xdiff/2/(zoom + step_zoom));
                            x_shift += xdiff;

                            float ydiff = zoom * y_size - (zoom + step_zoom) * y_size;
                            ydiff = (int)(ydiff/2/(zoom + step_zoom));
                            y_shift += (int)ydiff;
                            zoom += step_zoom;
                        }
                        break;

                    case SDLK_KP_MINUS:
                        if (zoom > step_zoom )
                        {
                            float xdiff = zoom * x_size - (zoom - step_zoom) * x_size;
                            xdiff = (int)(xdiff/2/(zoom));
                            x_shift += xdiff;

                            float ydiff = zoom * y_size - (zoom - step_zoom) * y_size;
                            ydiff = (int)(ydiff/2/zoom);
                            y_shift += (int)ydiff;
                            zoom -= step_zoom ;
                        }
                        break;
                    case SDLK_p:
                         if (pause) 
                            pause = 0;
                        else pause = 1;
                        break;
                    default:
                        break;
                }
            
            }
        }
}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv){
    
    int isRunning = 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_EXIT();
    }

    window = SDL_CreateWindow("Galaxy", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1600,900,0);

    if (window == NULL)
        SDL_EXIT();

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
        SDL_EXIT();

    
    
    if (SDL_RenderClear(renderer) != 0)
    {
        SDL_EXIT();
    }
    if (SDL_SetRenderDrawColor(renderer, 112,168,237, SDL_ALPHA_OPAQUE) != 0)
        SDL_EXIT();
    

    

    SDL_RenderPresent(renderer);
    Color white = {255,255,255};
    Color darkOrange = {255,87,51};
    Color lightOrange = {255,147,51};
    Color turquoise = {51,219,255};
    Color blue = {51,156,255};
    Color darkBlue = {7,4,147};
    Color lightBlue = {144,218,253};
    Color yellow = {235,227,56};
    Color lightYellow = {237,232,134};
    Color green = {62,221,42};
    Color lightGreen = {141,238,130};
    Color darkGreen = {37,158,22};
    Color red = {240,27,27};


    Body* b = malloc(sizeof(Body));
    b->pos = malloc(sizeof(Vec2));
    b->speed = malloc(sizeof(Vec2));
    b->acc = malloc(sizeof(Vec2));

    b->pos->x = 800;b->pos->y = 150;
    b->speed->x=15;b->speed->y=0;
    b->acc->x=0;b->acc->y=0;
    b->radius = 10;
    b->mass = 5;
    b->color = green;

    Body* venus = malloc(sizeof(Body));
    venus->pos = malloc(sizeof(Vec2));
    venus->speed = malloc(sizeof(Vec2));
    venus->acc = malloc(sizeof(Vec2));

    venus->pos->x = 800;venus->pos->y =600;
    venus->speed->x=-20;venus->speed->y=0;
    venus->acc->x=0;venus->acc->y=0;
    venus->radius = 10;
    venus->mass = 5;
    venus->color = darkOrange;



    Body* sun = malloc(sizeof(Body));
    sun->pos = malloc(sizeof(Vec2));
    sun->speed = malloc(sizeof(Vec2));
    sun->acc = malloc(sizeof(Vec2));

    sun->pos->x = 800;sun->pos->y = 450;
    sun->speed->x=0;sun->speed->y=0;
    sun->acc->x=0;sun->acc->y=0;
    sun->radius = 30;
    sun->mass = 3000;
    sun->color = yellow;

    Body* sun2 = malloc(sizeof(Body));
    sun2->pos = malloc(sizeof(Vec2));
    sun2->speed = malloc(sizeof(Vec2));
    sun2->acc = malloc(sizeof(Vec2));

    sun2->pos->x = 0;sun2->pos->y = 0;
    sun2->speed->x=2;sun2->speed->y=2;
    sun2->acc->x=0;sun2->acc->y=0;
    sun2->radius = 35;
    sun2->mass = 3000;
    sun2->color = lightBlue;

    listBody * planets = malloc(sizeof(listBody));
    planets->body = venus;
    planets->next = NULL;
    //addList(b, &planets);
    //addList(addPlanet(), &planets);
   

    listBody * stars = malloc(sizeof(listBody));
    stars->body = sun;
    stars->next = NULL;
    //addList(addStar(), &stars);

    for (int i = 0; i < 5; i++)
    {
           addSolarSystem(&stars, &planets);

    }
    



    int i = 200;
    

    float temps;
    clock_t t1, t2;
    t1 = clock();

    while (i>0 && isRunning)
    {
        keys(&isRunning);        
        
        

        
        
        if (SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE) != 0)
            SDL_EXIT();
        SDL_RenderClear(renderer);
       
if (!pause)
        {
        refreshList(&planets, &stars);

        refreshPosition(&planets);
        refreshPosition(&stars);
        }

        SDL_DrawList(&planets, renderer);
        SDL_DrawList(&stars, renderer);


        SDL_RenderPresent(renderer);
        //SDL_Delay(30);
        i--;
        


    }

    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", temps);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

;

    return 0;
}

 

//gcc *.c -lm $(sdl2-config --cflags --libs -ldl ) 
#endif