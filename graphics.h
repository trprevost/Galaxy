#ifndef GRAPHICS
#define GRAPHICS

#include <SDL2/SDL.h>
#include "list.h"

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

void SDL_DrawBody(Body * b, SDL_Renderer *renderer  );

void SDL_DrawList(listBody ** planets, SDL_Renderer *renderer  );

#endif