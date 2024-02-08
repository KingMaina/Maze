#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_

#include <stddef.h>

/* Boolean values */
#define TRUE 1
#define FALSE 0

/* Screen dimentions */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Raycasting */
#define TWO_PI 2 * M_PI /* 2 * PI or 360 degrees */
#define FOV_ANGLE 60 * (M_PI / 180) /* Field of view in radians */
#define TILE_SIZE 64
#define NUM_RAYS SCREEN_WIDTH /* Number of rays to cast */
#define PROJ_PLANE_DIST (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2) /* Projection plane distance */

/* Miscellaneous */
#define UNUSED __attribute__((unused))

#endif /* __CONSTANTS_H_ */