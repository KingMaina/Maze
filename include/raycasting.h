#ifndef __RAYCAST__H
#define __RAYCAST__H

#include "constants.h"
#include "player.h"
#include "game_map.h"
#include "initialize.h"


/* Map dimensions*/
#define MAP_SCALE_FACTOR 0.25
#define MAP_NUMBER_ROWS 10
#define MAP_NUMBER_COLS 16

/**
 * struct Ray - A structure representing a ray
 * @rayAngle: The angle of the ray
 * @wallSideHitX: The x coordinate of the wall hit
 * @wallSideHitY: The y coordinate of the wall hit
 * @distance: The distance from the player to the wall hit
 * @wasHitVertical: Whether the wall hit was vertical or not
 * @isRayFacingUp: Whether the ray is facing up
 * @isRayFacingDown: Whether the ray is facing down
 * @isRayFacingLeft: Whether the ray is facing left
 * @isRayFacingRight: Whether the ray is facing right
 * @wallHitContent: The content of the wall hit
 * Description: A structure representing a ray
*/
typedef struct Ray
{
    float rayAngle; /* The angle of the ray */
    float wallSideHitX; /* The x coordinate of the wall hit */
    float wallSideHitY; /* The y coordinate of the wall hit */
    float distance; /* The distance from the player to the wall hit */
    int wasHitVertical; /* Whether the wall hit was vertical or not */
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} Rays[NUM_RAYS];

void cast_all_rays(Player *player, Rays *rays, const int (*)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS]);
void cast_ray(Player *player, Rays *rays,  const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS], float rayAngle, int columnStripIndex);
void draw_rays(SDL_Instance *instance, Player *player, Rays rays[NUM_RAYS]);
int is_wall_at(const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS], float x, float y);
int distance_between_points(float x1, float y1, float x2, float y2);
int draw_map(SDL_Instance *, const int (*)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS]);
void renderRays(SDL_Instance *instance, Player *player, Rays rays[NUM_RAYS]);


#endif /* __RAYCAST__H */