#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "constants.h"
#include "upng.h"

// Reading png files and loading information to the colour buffers
typedef struct {
    upng_t* upngTexture;
    int width;
    int height;
    uint32_t* texture_buffer;
} texture_t;

texture_t getTexture(int textureIndex);

void loadWallTextures();
void freeWallTextures();

#endif