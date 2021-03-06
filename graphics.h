#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>
#include "list.h"


int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void SDL_DrawBody(Body * b, SDL_Renderer *renderer  );

void SDL_DrawList(SDL_Renderer *renderer  );

#endif