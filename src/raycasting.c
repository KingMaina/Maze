#include "../include/initialize.h"
#include "../include/raycasting.h"
#include "../include/player.h"
#include "../include/constants.h"
#include "../include/game_map.h"

/**
 * cast_all_rays - Casts all rays
 * @player: A pointer to the player
 * Description: Casts all rays
 *
 * Return: void
 */
void cast_all_rays(Player *player, Rays *rays, const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS])
{
    int columnStrip;

    for (columnStrip = 0; columnStrip < NUM_RAYS; ++columnStrip)
    {
        float rayAngle = player->rotationAngle + atan(
                                                     (columnStrip - NUM_RAYS / 2) / PROJ_PLANE_DIST);
        /* Ensure the ray angle is between 0 and 2 * PI */
        rayAngle = remainder(rayAngle, TWO_PI);
        if (rayAngle < 0)
            rayAngle = TWO_PI + rayAngle;
        cast_ray(player, rays, map, rayAngle, columnStrip);
    }
}

/**
 * cast_ray - Casts a ray
 * @player: A pointer to the player
 * @rayAngle: The angle of the ray
 * @columnStripIndex: The index of the column strip
 * Description: Casts a ray
 *
 * Return: void
 */
void cast_ray(
    Player *player,
    Rays *rays,
    const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS],
    float rayAngle,
    int columnStripIndex)
{
    float xintercept = 0, yintercept = 0;
    float xstep = 0, ystep = 0;
    float nextXPoint = 0, nextYPoint = 0;

    int isRayFacingUpwards = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingDownwards = !isRayFacingUpwards;
    int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;

    /* Horizontal grid intersection */
    int isHorizontalWallHit = 0;
    int horizontalWallValue = 0;
    float horizontalWallHitX = 0, horizontalWallHitY = 0;

    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDownwards ? TILE_SIZE : 0;

    /* Calculate x coordinate of closest grid intersection */
    xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

    /* Calculate increments */
    ystep = TILE_SIZE;
    ystep *= isRayFacingUpwards ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    nextXPoint = xintercept;
    nextYPoint = yintercept;

    while (nextXPoint >= 0 && nextXPoint <= SCREEN_WIDTH &&
           nextYPoint >= 0 && nextYPoint <= SCREEN_HEIGHT)
    {
        if (is_wall_at(map, nextXPoint, nextYPoint + (isRayFacingUpwards ? -1 : 0)))
        {
            isHorizontalWallHit = 1;
            horizontalWallHitX = nextXPoint;
            horizontalWallHitY = nextYPoint;
            horizontalWallValue = (*map)[(int)floor(nextYPoint / TILE_SIZE)][(int)floor(nextXPoint / TILE_SIZE)];
            break;
        }
        else
        {
            nextXPoint += xstep;
            nextYPoint += ystep;
        }
    }

    /* Vertical grid intersection */
    int isVerticalWallHit = 0;
    int verticalWallValue = 0;
    float verticalWallHitX = 0, verticalWallHitY = 0;

    /* Calculate x coordinate of closest vertical grid intersection */
    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    /* Calculate y coordinate of closest vertical grid intersection */
    yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

    /* Calculate increments */
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUpwards && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDownwards && ystep < 0) ? -1 : 1;

    float nextVerticalXPoint = xintercept;
    float nextVerticalYPoint = yintercept;

    while (nextVerticalXPoint >= 0 && nextVerticalXPoint <= SCREEN_WIDTH &&
           nextVerticalYPoint >= 0 && nextVerticalYPoint <= SCREEN_HEIGHT)
    {
        if (is_wall_at(map, nextVerticalXPoint + (isRayFacingLeft ? -1 : 0), nextVerticalYPoint))
        {
            isVerticalWallHit = 1;
            verticalWallHitX = nextVerticalXPoint;
            verticalWallHitY = nextVerticalYPoint;
            verticalWallValue = (*map)[(int)floor(nextVerticalYPoint / TILE_SIZE)][(int)floor(nextVerticalXPoint / TILE_SIZE)];
            break;
        }
        else
        {
            nextVerticalXPoint += xstep;
            nextVerticalYPoint += ystep;
        }
    }

    /* Calculate the distance of the horizontal and vertical intersections */
    float horizontalHitDistance = isHorizontalWallHit
                                      ? distance_between_points(player->x, player->y, horizontalWallHitX, horizontalWallHitY)
                                      : FLT_MAX;
    float verticalHitDistance = isVerticalWallHit
                                    ? distance_between_points(player->x, player->y, verticalWallHitX, verticalWallHitY)
                                    : FLT_MAX;

    /* Determine which distance is closer */
    if (horizontalHitDistance < verticalHitDistance)
    {
        rays[columnStripIndex]->distance = horizontalHitDistance;
        rays[columnStripIndex]->wallSideHitX = horizontalWallHitX;
        rays[columnStripIndex]->wallSideHitY = horizontalWallHitY;
        rays[columnStripIndex]->wallHitContent = horizontalWallValue;
        rays[columnStripIndex]->wasHitVertical = 0;
    }
    else
    {
        rays[columnStripIndex]->distance = verticalHitDistance;
        rays[columnStripIndex]->wallSideHitX = verticalWallHitX;
        rays[columnStripIndex]->wallSideHitY = verticalWallHitY;
        rays[columnStripIndex]->wallHitContent = verticalWallValue;
        rays[columnStripIndex]->wasHitVertical = 1;
    }
    rays[columnStripIndex]->rayAngle = rayAngle;
    rays[columnStripIndex]->isRayFacingDown = isRayFacingDownwards;
    rays[columnStripIndex]->isRayFacingUp = isRayFacingUpwards;
    rays[columnStripIndex]->isRayFacingLeft = isRayFacingLeft;
    rays[columnStripIndex]->isRayFacingRight = isRayFacingRight;

    printf("Ray angle: %f\n", rayAngle);
    printf("Column strip index: %d\n", columnStripIndex);
}

int is_wall_at(const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS], float x, float y)
{
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
        return (1);
    int gridXIndex = floor(x / TILE_SIZE);
    int gridYIndex = floor(y / TILE_SIZE);

    return ((*map)[gridYIndex][gridXIndex] != 0);
}

void draw_rays(SDL_Instance *instance, Player *player, Rays rays[NUM_RAYS])
{
    int i;

    SDL_SetRenderDrawColor(instance->renderer, 0, 255, 0, 255);
    for (i = 0; i < NUM_RAYS; i++)
    {
        SDL_RenderDrawLine(instance->renderer, player->x * MAP_SCALE_FACTOR,
                           player->y * MAP_SCALE_FACTOR,
                           rays[i]->wallSideHitX * MAP_SCALE_FACTOR,
                           rays[i]->wallSideHitY * MAP_SCALE_FACTOR);
    }
}

int distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}