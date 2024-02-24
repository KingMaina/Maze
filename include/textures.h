#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "constants.h"
#include "upng.h"

/**
* struct Texture - texture struct
* @upngTexture: upng texture
* @texture_buffer: texture buffer
* @width: width of the texture
* @height: height of the texture
*/
typedef struct Texture
{
	upng_t *upngTexture;
	uint32_t *texture_buffer;
	int width;
	int height;
} texture_t;

texture_t getTexture(texture_t wallTextures[NUM_TEXTURES], int textureIndex);

void loadWallTextures(texture_t wallTextures[NUM_TEXTURES]);
void freeWallTextures(texture_t wallTextures[NUM_TEXTURES]);

#endif /* TEXTURES_H */
