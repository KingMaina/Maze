#include "../include/init.h"
#include "../include/textures.h"

texture_t wallTextures[NUM_TEXTURES];

static const char *textureFileNames[NUM_TEXTURES] = {
	"./assets/images/bonewall.png",
	"./assets/images/bonewallpillar.png",
	"./assets/images/bonewallwithgrass.png",
	"./assets/images/bonewall.png",
	"./assets/images/bonewall.png",
	"./assets/images/bonewall.png",
	"./assets/images/bonewallpillar.png",
	"./assets/images/bonewall.png",
	"./assets/images/bonewall.png",
	"./assets/images/bonewall.png",
};

/**
* loadWallTextures - load all the wall textures
*
* Return: void
*/
void loadWallTextures(void)
{
	/* Load all the PNG textures from the filepaths */
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_t *upng;

		upng = upng_new_from_file(textureFileNames[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				wallTextures[i].upngTexture = upng;
				wallTextures[i].width = upng_get_width(upng);
				wallTextures[i].height = upng_get_height(upng);
				wallTextures[i].texture_buffer = (uint32_t *)upng_get_buffer(upng);
			}
		}
	}
}

/**
* freeWallTextures - free all the wall textures from memory
*
* Return: void
*/
void freeWallTextures(void)
{
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		upng_free(wallTextures[i].upngTexture);
	}
}

/**
* getTexture - get the texture from the wallTextures array
* @textureIndex: index of the texture
*
* Return: texture at the index
*/
texture_t getTexture(int textureIndex)
{
	return (wallTextures[textureIndex]);
}

/**
* clearColorBuffer - clear the color buffer
* @colorBuffer: color buffer
* @color: color to clear the buffer with
*
* Return: void
*/
void clearColorBuffer(uint32_t *colorBuffer, uint32_t color)
{
	/* Clear the entire color buffer with the color black */
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			colorBuffer[(SCREEN_WIDTH * y) + x] = color;
		}
	}
}

/**
* renderColorBuffer - render the color buffer
* @instance: SDL instance
* @colorBufferTexture: color buffer texture
* @colorBuffer: color buffer
*
* Return: void
*/
void renderColorBuffer(SDL_Instance *instance,
	SDL_Texture *colorBufferTexture,
	uint32_t *colorBuffer
)
{
	/* Copy over all the texture information from the buffer */
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)((uint32_t)SCREEN_WIDTH * sizeof(uint32_t)));
	SDL_RenderCopy(instance->renderer, colorBufferTexture, NULL, NULL);
}
