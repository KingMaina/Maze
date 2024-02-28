#include "../include/init.h"
#include "../include/textures.h"

/**
* freeMemory - Free dynamic memory allocated in the game
* @instance: SDL instance
* @colorBufferTexture: color buffer texture
* @colorBuffer: color buffer
* @wallTextures: wall textures
*
* Return: void
*/
void freeMemory(SDL_Instance *instance, SDL_Texture **colorBufferTexture,
	uint32_t **colorBuffer, texture_t wallTextures[NUM_TEXTURES])
{
	/* Free the wall textures */
	freeWallTextures(wallTextures);

	/* Free the color buffer */
	free(*colorBuffer);
	*colorBuffer = NULL;

	/* Free the color buffer texture */
	SDL_DestroyTexture(*colorBufferTexture);
	*colorBufferTexture = NULL;

	/* Destroy the window and renderer */
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	instance->window = NULL;
	instance->renderer = NULL;

	/* Quit SDL */
	SDL_Quit();
}
