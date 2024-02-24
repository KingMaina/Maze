#include "../include/init.h"
#include "../include/textures.h"

/**
* freeMemory - Free dynamic memory allocated in the game
* @instance: SDL instance
* @colorBufferTexture: color buffer texture
* @colorBuffer: color buffer
*
* Return: void
*/
void freeMemory(SDL_Instance *instance, SDL_Texture *colorBufferTexture,
	uint32_t *colorBuffer)
{
	freeWallTextures();
	free(colorBuffer);
	colorBuffer = NULL;
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	instance->window = NULL;
	instance->renderer = NULL;
	SDL_Quit();
}
