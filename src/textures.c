#include <stdio.h>
#include "../include/textures.h"

texture_t wallTextures[NUM_TEXTURES];

// Array of texture file names for my images
static const char* textureFileNames[NUM_TEXTURES] = {
    "./assets/images/bonewall.png",
    "./assets/images/bonewallwithgrass.png",
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

void loadWallTextures(){
    // Load all the PNG textures from the filepaths
    for (int i = 0; i < NUM_TEXTURES; i++){
        upng_t* upng;

        upng = upng_new_from_file(textureFileNames[i]);
        if (upng != NULL){
            upng_decode(upng);
            // Saving the array of textures
            if (upng_get_error(upng) == UPNG_EOK) {
                wallTextures[i].upngTexture = upng;
                wallTextures[i].width = upng_get_width(upng);
                wallTextures[i].height = upng_get_height(upng);
                wallTextures[i].texture_buffer = (uint32_t*)upng_get_buffer(upng);
            }
        }
    }
}

void freeWallTextures(){
    for (int i = 0; i < NUM_TEXTURES; i++){
        upng_free(wallTextures[i].upngTexture);
    }
}

texture_t getTexture(int textureIndex) {

    return wallTextures[textureIndex];

}