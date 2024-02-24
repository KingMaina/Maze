#include "../include/init.h"
#include "../include/textures.h"

/**
 * createWorld - create the world
 * @player: player object
 * @rays: rays object
 * @colorBuffer: color buffer
 *
 * Return: void
*/
void createWorld(Player *player, Rays *rays, uint32_t *colorBuffer, texture_t wallTextures[NUM_TEXTURES])
{
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float perpDistance = rays[i]->distance * cos(rays[i]->rayAngle - player->rotationAngle); // Correct the fish-eye distortion
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        int wallStripHeight = (int)projectedWallHeight;

        /* Calculate top and bottom of walls */
        int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel; /* clamp to 0 */
        int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel; // clamp to 0

        /* Render the color of the ceiling */
        for (int y = 0; y < wallTopPixel; y++)
            colorBuffer[(SCREEN_WIDTH * y) + i] = 0xFF000000;

        int textureOffsetX;
        // calculate textureOffsetX
        if (rays[i]->wasHitVertical)
            // Perform offset for the vertical hit
            textureOffsetX = (int)rays[i]->wallHitY % TILE_SIZE;
        else
            // perform offset for the horizontal hit
            textureOffsetX = (int)rays[i]->wallHitX % TILE_SIZE;

        // get the correct texture id number from the map content
        int texNum = rays[i]->wallHitContent - 1;

        // Render wall from top to bottom
        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            // Calculate textureOffset Y
            int distanceFromTop = y + (wallStripHeight / 2) - (SCREEN_HEIGHT / 2);            // fix distortion due to clamping values
            int textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallStripHeight); // take into account that the size of the texture might have to be adjusted

            // Set the color of the wall based on the color from the texture in memory
            uint32_t texelColor = getTexture(wallTextures, texNum).texture_buffer[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
            colorBuffer[(SCREEN_WIDTH * y) + i] = texelColor;
        }

        // Render the color of the floor
        for (int y = wallBottomPixel; y < SCREEN_HEIGHT; y++)
        {
            colorBuffer[(SCREEN_WIDTH * y) + i] = 0xFF3A3419;
            // colorBuffer[(SCREEN_WIDTH * y) + i] = 0xFFFFFF19;
        }
    }
}

/**
 * mapHasWallAt - check if the map has a wall at the given x and y coordinates
 * @map: The game map
 * @x: x-coordinate
 * @y: y-coordinate
 *
 * Return: 1 if there is a wall, 0 otherwise
*/
int mapHasWallAt(int map[MAP_NUM_ROWS][MAP_NUM_COLS], float x, float y)
{
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
    {
        return EXEC_SUCCESS;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

/**
 * castRay - cast a ray
 * @player: player object
 * @rays: rays object
 * @map: The game map
 * @rayAngle: angle of the ray
 * @stripId: id of the strip
 *
 * Return: void
*/
void castRay(Player *player, Rays *rays, int map[MAP_NUM_ROWS][MAP_NUM_COLS],
float rayAngle, int stripId)
{
    rayAngle = normaliseAngle(rayAngle);

    int isRayFacingDownward = rayAngle > 0 && rayAngle < PI;
    int isRayFacingUpward = !isRayFacingDownward;

    int isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    //**Start Horizontal Ray-Grid Intersection Logic ********************************//
    int foundHorzWallHit = EXEC_FAIL;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDownward ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player->x + (yintercept - player->y) / tan(rayAngle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUpward ? -1 : 1;

    xstep = TILE_SIZE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment the xstep and ystep until player finds a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= SCREEN_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= SCREEN_HEIGHT)
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUpward ? -1 : 0);

        if (mapHasWallAt(map, xToCheck, yToCheck))
        {
            // found a wall Hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            // Devide the y and x to the tile size to get the index of the map, then save into a variable
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)]
                                 [(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = EXEC_SUCCESS;
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    //***** End Horizontal Ray-Grid Intersection Logic ********************************//

    //**Start Vertical Ray-Grid Intersection Logic ************************************//
    int foundVertWallHit = EXEC_FAIL;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = player->y + (xintercept - player->x) * tan(rayAngle);

    // Calculate the increment xstep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    // Calculate the increment ystep
    ystep = TILE_SIZE * tan(rayAngle);
    ystep *= (isRayFacingUpward && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDownward && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= SCREEN_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= SCREEN_HEIGHT)
    {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;

        if (mapHasWallAt(map, xToCheck, yToCheck))
        {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)]
                                 [(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = EXEC_SUCCESS;
            break;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }
    //***** End Vertical Ray-Grid Intersection Logic **********************************//

    // Calculate both horizontal and vertical hit distances and choose the closest one
    float horzHitDistance = foundHorzWallHit
                                ? distanceBetweenPoints(player->x, player->y, horzWallHitX, horzWallHitY)
                                : FLT_MAX;
    float vertHitDistance = foundVertWallHit
                                ? distanceBetweenPoints(player->x, player->y, vertWallHitX, vertWallHitY)
                                : FLT_MAX;

    // Keep the closest distance to the player
    if (vertHitDistance < horzHitDistance)
    {
        rays[stripId]->distance = vertHitDistance;
        rays[stripId]->wallHitX = vertWallHitX;
        rays[stripId]->wallHitY = vertWallHitY;
        rays[stripId]->wallHitContent = vertWallContent;
        rays[stripId]->wasHitVertical = EXEC_SUCCESS;
    }
    else
    {
        rays[stripId]->distance = horzHitDistance;
        rays[stripId]->wallHitX = horzWallHitX;
        rays[stripId]->wallHitY = horzWallHitY;
        rays[stripId]->wallHitContent = horzWallContent;
        rays[stripId]->wasHitVertical = EXEC_FAIL;
    }
    rays[stripId]->rayAngle = rayAngle;
    rays[stripId]->isRayFacingDownward = isRayFacingDownward;
    rays[stripId]->isRayFacingUpward = isRayFacingUpward;
    rays[stripId]->isRayFacingLeft = isRayFacingLeft;
    rays[stripId]->isRayFacingRight = isRayFacingRight;
}

/**
 * castAllRays - cast all rays
 * @player: player object
 * @rays: rays object
 * 
 * Return: void
 */
void castAllRays(Player *player,
Rays rays[], int map[MAP_NUM_ROWS][MAP_NUM_COLS])
{
    for (int col = 0; col < NUM_RAYS; col++)
    {
        float rayAngle = player->rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
        castRay(player, rays, map, rayAngle, col);
    }
}
