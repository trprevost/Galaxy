#ifndef MAIN
#define MAIN

#include <SDL2/SDL.h>
#include <stdio.h>
#include "graphics.h"
#include "physics.h"
#include "init.h"
#include "calculs.h"




int x_shift = 0;
int y_shift = 0;
int static x_size = 1600;
int static y_size = 900;
int pixel_step = 5;
float zoom = 1;
float step_zoom = 0.25;
int pause = 0;
struct Body* tabPlanets[800];
struct Body* tabStars[100];
int nbPlanets = 0;
int nbStars = 0;

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

void destroyTab(){
    for (int i = 0; i < nbPlanets; i++)
    {
        free(tabPlanets[i]->acc);
        free(tabPlanets[i]->pos);
        free(tabPlanets[i]->speed);
        free(tabPlanets[i]);
    }
    for (int i = 0; i < nbStars; i++)
    {
        free(tabStars[i]->acc);
        free(tabStars[i]->pos);
        free(tabStars[i]->speed);
        free(tabStars[i]);
    }
    
}
/**
 * all keys events
 **/
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
  

    for (int i = 0; i < 100; i++)
    {
           addSolarSystem();
    }
    


    //iterations
    int i = 2000;
    

    //time calculation
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);

    while (i>0 && isRunning)
    {
        keys(&isRunning);        
        
    
        if (SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE) != 0)
            SDL_EXIT();
        SDL_RenderClear(renderer);
       
if (!pause)
        {
        refreshList();
        refreshPosition();
        i--;
        }

        SDL_DrawList(renderer);
        SDL_RenderPresent(renderer);
        //SDL_Delay(30);
        
        


    }


    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("time = %f seconds\n", elapsed);


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    destroyTab();

    return 0;
}

 

//gcc *.c -fopenmp -lm $(sdl2-config --cflags --libs -ldl ) && OMP_NUM_THREADS=2 ./a.out
#endif