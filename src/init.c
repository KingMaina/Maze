#include "../include/init.h"
#include "../include/constants.h"

/**
* initializeWindow - Initialize the SDL window and renderer
* @instance: SDL instance
*
* Return: 1 on success, 0 on failure
*/
int initializeWindow(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return (EXEC_FAIL);
	}
	instance->window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_FULLSCREEN);
	if (!instance->window)
	{
		fprintf(stderr, "Error creating SDL window.\n");
		return (EXEC_FAIL);
	}
	instance->renderer = SDL_CreateRenderer(instance->window, -1, 0);
	if (!instance->renderer)
	{
		fprintf(stderr, "Error creating SDL renderer.\n");
		return (EXEC_FAIL);
	}
	SDL_SetRenderDrawBlendMode(instance->renderer, SDL_BLENDMODE_BLEND);

	return (EXEC_SUCCESS);
}
