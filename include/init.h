#ifndef INIT_H_
#define INIT_H_

#include <SDL2/SDL.h>

/**
 * struct Sdl_Instance - SDL instance
 * @window: SDL window
 * @renderer: SDL renderer
 * 
 * Description: SDL instance
*/
typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance; 

int initializeWindow(SDL_Instance *instance);
void destroyWindow(SDL_Instance *instance, SDL_Texture *, uint32_t *);

#endif /* INIT_H_ */