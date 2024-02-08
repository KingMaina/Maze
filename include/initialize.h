#ifndef __INIT__H
#define __INIT__H

/* Libraries */
#undef __STRICT_ANSI__
#include <math.h>

#include "SDL2/SDL.h"
#include <stdio.h>
#include "../include/constants.h"

/**
 * struct SDL_Instance - The SDL window and renderer
 * @window: The game window
 * @renderer: The game renderer
*/
typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int initialize_game(SDL_Instance *);
void destroy_game(SDL_Instance *);

#endif /* __INIT__H */