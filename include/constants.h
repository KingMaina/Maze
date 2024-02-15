#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>

#define EXEC_FAIL 0
#define EXEC_SUCCESS 1

#define PI 3.14159265
#define TWO_PI 6.28318530

// Raycasting constants:
#define TILE_SIZE 64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define NUM_TEXTURES 11

#define MAP_SCALE_FACTOR 0.25

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS SCREEN_WIDTH

// calc how far the player is from the projection plane
#define DIST_PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))

// DeltaTime
#define FPS 30                         // Frames per second
#define FRAME_TIME_LENGHT (1000 / FPS) // expected milliseconds in a frame

#endif