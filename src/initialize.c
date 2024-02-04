#include "headers/init.h"
#include "headers/constants.h"

/**
 * initialize_game - Initializes the game window and renderer
 * @instance: SDL Instance for window and renderer
 *
 * Return: 1 if game successfully intializes, 0 otherwise
*/
int initialize_game(SDL_Instance *instance)
{
    if (SDL_Init(SDL_INIT_VIDEO) != FALSE)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return (FALSE);
    }
    instance->window = SDL_CreateWindow(
        "Maze",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_BORDERLESS
        );
    if (instance->window == NULL)
    {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        return (FALSE);
    }
    instance->renderer= SDL_CreateRenderer(
        instance->window,
        -1,
        SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED
    );
    if (instance->renderer == NULL)
    {
        fprintf(stderr, "Error initializing SDL renderer: %s\n", SDL_GetError());
        return (FALSE);
    }
    SDL_SetRenderDrawBlendMode(
        instance->renderer,
        SDL_BLENDMODE_BLEND
    );
    return (TRUE);
}

/**
 * destroy_game - Destroys the game window and renderer
 * @instance: SDL Instance for window and renderer
 *
 * Return: void
*/
void destroy_game(SDL_Instance *instance)
{
    SDL_DestroyRenderer(instance->renderer);
    SDL_DestroyWindow(instance->window);
    SDL_Quit();
}
