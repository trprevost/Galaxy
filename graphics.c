#include"graphics.h"
#include"omp.h"
extern int y_shift;
extern int x_shift;
extern float zoom;
int static x_size = 1600;
int static y_size = 900;

extern struct Body* tabPlanets[500];
extern struct Body* tabStars[100];
extern int nbPlanets;
extern int nbStars;

int isOnScreen(int x, int y)
{
    /*f (x < x_shift-30 || x > x_shift + x_size + 30)
    {
        return 0;
    }
    if (y < y_shift-30 || y > y_shift + y_size + 30)
    {
        return 0;
    }*/
    
    return 1;
}



/**
 * draw a filled circle
 **/
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


/**
 * Draw a body on the screen
 **/
void SDL_DrawBody(Body * b, SDL_Renderer *renderer  ){
    int x = (b->pos->x + x_shift)*zoom;
    int y = (b->pos->y + y_shift)*zoom;
    SDL_RenderFillCircle(renderer, x, y,b->radius*zoom);
}



/**
 * Call SDL_DrawBody()   for all stars and planets with the right color
 **/
void SDL_DrawList(SDL_Renderer *renderer  )
{

    for (int i = 0; i < nbStars; i++)
    {

        if (isOnScreen(tabStars[i]->pos->x,tabStars[i]->pos->y))
        {
            //change color
            if (SDL_SetRenderDrawColor(renderer, tabStars[i]->color.r,tabStars[i]->color.g,tabStars[i]->color.b, SDL_ALPHA_OPAQUE) != 0)
            {;}//SDL_EXIT();
            
            SDL_DrawBody(tabStars[i], renderer);
        }
        
       
        
    }

    for (int i = 0; i < nbPlanets; i++)
    {
        if (isOnScreen(tabPlanets[i]->pos->x,tabPlanets[i]->pos->y))
        {
        if (SDL_SetRenderDrawColor(renderer, tabPlanets[i]->color.r,tabPlanets[i]->color.g,tabPlanets[i]->color.b, SDL_ALPHA_OPAQUE) != 0)
            {;}//SDL_EXIT();
            
        SDL_DrawBody(tabPlanets[i], renderer);
        }
    }
}