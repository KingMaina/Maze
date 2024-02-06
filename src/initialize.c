#include "../include/initialize.h"
#include "../include/constants.h"

/**
 * initialize_game - Initializes the game window and renderer
 * @instance: SDL Instance for window and renderer
 *
 * Return: 1 if game successfully intializes, 0 otherwise
*/
int initialize_game(SDL_Instance *instance)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return (1);
    }
    instance->window = SDL_CreateWindow(
        "Maze game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
        );
    if (instance->window == NULL)
    {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        destroy_game(instance);
        return (1);
    }
    instance->renderer= SDL_CreateRenderer(
        instance->window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (instance->renderer == NULL)
    {
        fprintf(stderr, "Error initializing SDL renderer: %s\n", SDL_GetError());
        destroy_game(instance);
        return (1);
    }
    SDL_SetRenderDrawBlendMode(
        instance->renderer,
        SDL_BLENDMODE_BLEND
    );
    return (0);
}

/**
 * destroy_game - Destroys the game window and renderer
 * @instance: SDL Instance for window and renderer
 *
 * Return: void
*/
void destroy_game(SDL_Instance *instance)
{
    if (instance->renderer != NULL)
    {
        SDL_DestroyRenderer(instance->renderer);
    }
    if (instance->window != NULL)
    {
        SDL_DestroyWindow(instance->window);
    }
    SDL_Quit();
}
