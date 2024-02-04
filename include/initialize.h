#ifndef __INIT__H
#define __INIT__H

#include "SDL2/SDL.h"
#include <stdio.h>

/**
 * struct SDL_Instance - The SDL window and rendererer
 * @window: The game window
 * @renderer: The game renderer
*/
typedef struct SDL_Instance {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int initialize_game(SDL_Instance *);
void destroy_game(SDL_Instance *);


#endif /* __INIT__H */