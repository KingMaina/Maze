#include <stdio.h>
#include <stdint.h>

#include <limits.h>
#include <math.h>
#include <float.h>
#include "../include/init.h"
#include "../include/constants.h"
#include "../include/textures.h"

//********************************* MAP *******************************************//
const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 1},
    {1, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 2, 2, 2, 2, 2, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 0, 2, 2, 2, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 1, 2, 0, 0, 2, 0, 2, 2, 2, 2, 2, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
//*********************************************************************************//

// Struct to hold player data
typedef struct Player
{
    float x;
    float y;
    float width;
    float height;
    int turnDirection; // -1 for left, +1 for right
    int walkDirection; // -1 for back, +1 for forward
    float rotationAngle;
    float walkSpeed;
    float turnSpeed; // angles per second
} Player;            // declare variable name for the player struct

// Struct/container to hold the ray 'object'
struct Ray
{
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUpward;
    int isRayFacingDownward;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} rays[NUM_RAYS]; // array of rays

int isGameRunning = EXEC_FAIL;
int ticksLastFrame;
// Color buffer = array of pixels per line
SDL_Texture *colorBufferTexture; // using SDL to display array of pixels representing texture
Player player;

void destroyWindow(SDL_Instance *instance, SDL_Texture *colorBufferTexture, uint32_t *colorBuffer)
{
    freeWallTextures();
    free(colorBuffer);                      // clearing previously allocated memory for the buffer
    SDL_DestroyTexture(colorBufferTexture); // destroy textures
    SDL_DestroyRenderer(instance->renderer);
    SDL_DestroyWindow(instance->window);
    SDL_Quit;
}
//*********************************************************************************//

void setup(SDL_Instance *instance, Player *player, uint32_t **colorBuffer)
{
    // Setting up the Player
    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;
    player->width = 1;
    player->height = 1;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = PI / 2;
    player->walkSpeed = 100;
    player->turnSpeed = 45 * (PI / 180);

    // Allocate enough memory to hold the entire screen in the color buffer
    *colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * SCREEN_WIDTH * SCREEN_HEIGHT * 8);

    // Create a SDL_Texture to display the color buffer
    colorBufferTexture = SDL_CreateTexture(
        instance->renderer,          // create textures to renderer
        SDL_PIXELFORMAT_RGBA32,      // pixel format -> alpha RGB fill
        SDL_TEXTUREACCESS_STREAMING, // FLAG -> able to change texture in real time
        SCREEN_WIDTH,                // size
        SCREEN_HEIGHT                // size
    );

    // Using uPNG library to decode all png files and loading the wallTextures array
    loadWallTextures();
}

// /////////////////////////////////////////////////////////////////////////////// //
//*************************** PLAYER MOVEMENT *************************************//
int mapHasWallAt(float x, float y)
{
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
    {
        return EXEC_SUCCESS;
    }
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

void movePlayer(float deltaTime)
{
    player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
    float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

    float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
    float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

    // perform wall colision
    // Only assign newPlayer position when not overlapping wall position
    if (!mapHasWallAt(newPlayerX, newPlayerY))
    {
        player.x = newPlayerX;
        player.y = newPlayerY;
    }
}
//*********************************************************************************//

// /////////////////////////////////////////////////////////////////////////////// //
//*************************** RENDER PLAYER ***************************************//
void renderPlayer(SDL_Instance *instance)
{
    SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);
    SDL_Rect playerRect = {
        player.x * MAP_SCALE_FACTOR,
        player.y * MAP_SCALE_FACTOR,
        player.width * MAP_SCALE_FACTOR,
        player.height * MAP_SCALE_FACTOR};
    SDL_RenderFillRect(instance->renderer, &playerRect);

    SDL_RenderDrawLine(
        instance->renderer,
        MAP_SCALE_FACTOR * player.x,
        MAP_SCALE_FACTOR * player.y,
        MAP_SCALE_FACTOR * player.x + cos(player.rotationAngle) * 40,
        MAP_SCALE_FACTOR * player.y + sin(player.rotationAngle) * 40);
}
//*********************************************************************************//

// Ensure the angle of a Ray holds a positive number
float normaliseAngle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle = TWO_PI + angle;
    return angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// /////////////////////////////////////////////////////////////////////////////// //
//************************ RAY CASTING ********************************************//
void castRay(float rayAngle, int stripId)
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
    yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDownward ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

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

        if (mapHasWallAt(xToCheck, yToCheck))
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
    xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

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

        if (mapHasWallAt(xToCheck, yToCheck))
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
                                ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
                                : FLT_MAX;
    float vertHitDistance = foundVertWallHit
                                ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
                                : FLT_MAX;

    // Keep the closest distance to the player
    if (vertHitDistance < horzHitDistance)
    {
        rays[stripId].distance = vertHitDistance;
        rays[stripId].wallHitX = vertWallHitX;
        rays[stripId].wallHitY = vertWallHitY;
        rays[stripId].wallHitContent = vertWallContent;
        rays[stripId].wasHitVertical = EXEC_SUCCESS;
    }
    else
    {
        rays[stripId].distance = horzHitDistance;
        rays[stripId].wallHitX = horzWallHitX;
        rays[stripId].wallHitY = horzWallHitY;
        rays[stripId].wallHitContent = horzWallContent;
        rays[stripId].wasHitVertical = EXEC_FAIL;
    }
    rays[stripId].rayAngle = rayAngle;
    rays[stripId].isRayFacingDownward = isRayFacingDownward;
    rays[stripId].isRayFacingUpward = isRayFacingUpward;
    rays[stripId].isRayFacingLeft = isRayFacingLeft;
    rays[stripId].isRayFacingRight = isRayFacingRight;
}
//*********************************************************************************//

void castAllRays()
{
    for (int col = 0; col < NUM_RAYS; col++)
    {
        float rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
        castRay(rayAngle, col);
    }
}

// /////////////////////////////////////////////////////////////////////////////// //
//*************************** RENDER MAP ******************************************//
void renderMap(SDL_Instance *instance)
{
    for (int i = 0; i < MAP_NUM_ROWS; i++)
    {
        for (int j = 0; j < MAP_NUM_COLS; j++)
        {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;
            int tileColor = map[i][j] != 0 ? 200 : 0; // ternary statement - if the value at
            // map[i][j] is not equal to 0, then set tileColor to 255; otherwise, set it to 0

            SDL_SetRenderDrawColor(instance->renderer, tileColor, tileColor, tileColor, 255);
            SDL_Rect mapTileRect = {
                tileX * MAP_SCALE_FACTOR,
                tileY * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR};
            SDL_RenderFillRect(instance->renderer, &mapTileRect);
        }
    }
}
//*********************************************************************************//

// /////////////////////////////////////////////////////////////////////////////// //
//*************************** RENDER RAYS ******************************************//
void renderRays(SDL_Instance *instance)
{
    SDL_SetRenderDrawColor(instance->renderer, 255, 0, 0, 255);
    for (int i = 0; i < NUM_RAYS; i++)
    {
        SDL_RenderDrawLine(
            instance->renderer,
            MAP_SCALE_FACTOR * player.x, // start position of ray
            MAP_SCALE_FACTOR * player.y,
            MAP_SCALE_FACTOR * rays[i].wallHitX, // end position of ray
            MAP_SCALE_FACTOR * rays[i].wallHitY);
    }
}
//*********************************************************************************//

// /////////////////////////////////////////////////////////////////////////////// //
//*************************** USER INPUT ******************************************//
void handleInputEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
    {
        isGameRunning = EXEC_FAIL;
        break;
    }
    case SDL_KEYDOWN:
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
            isGameRunning = EXEC_FAIL;
        if (event.key.keysym.sym == SDLK_UP)
            player.walkDirection = +1;
        if (event.key.keysym.sym == SDLK_DOWN)
            player.walkDirection = -1;
        if (event.key.keysym.sym == SDLK_RIGHT)
            player.turnDirection = +1;
        if (event.key.keysym.sym == SDLK_LEFT)
            player.turnDirection = -1;
        break;
    }
    case SDL_KEYUP:
    {
        if (event.key.keysym.sym == SDLK_UP)
            player.walkDirection = 0;
        if (event.key.keysym.sym == SDLK_DOWN)
            player.walkDirection = 0;
        if (event.key.keysym.sym == SDLK_RIGHT)
            player.turnDirection = 0;
        if (event.key.keysym.sym == SDLK_LEFT)
            player.turnDirection = 0;
        break;
    }
    }
}
//*********************************************************************************//

void updateGame()
{
    //*************************** SDL_Delay ***************************************//
    // delay some time until the target frame time length is reached
    // http://wiki.libsdl.org/SDL2/SDL_Delay

    // Compute how long before the target frame time in milliseconds is reached
    int timeToWait = FRAME_TIME_LENGHT - (SDL_GetTicks() - ticksLastFrame);
    // Only delay execution if program is running too fast
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGHT)
    {
        SDL_Delay(timeToWait);
    }
    // Compute the delta time to be used as an update factor when changing game objects
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
    // Store the milliseconds of the current frame to be used in the future
    ticksLastFrame = SDL_GetTicks();
    //*****************************************************************************//

    movePlayer(deltaTime);
    castAllRays();
}

void createWorld(uint32_t *colorBuffer)
{
    for (int i = 0; i < NUM_RAYS; i++)
    {
        float perpDistance = rays[i].distance * cos(rays[i].rayAngle - player.rotationAngle); // Correct the fish-eye distortion
        float projectedWallHeight = (TILE_SIZE / perpDistance) * DIST_PROJ_PLANE;

        int wallStripHeight = (int)projectedWallHeight;

        // Calculate top and bottom of walls
        int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallStripHeight / 2);
        wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel; // clamp to 0
        int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallStripHeight / 2);
        wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel; // clamp to 0

        // Render the color of the ceiling
        for (int y = 0; y < wallTopPixel; y++)
            colorBuffer[(SCREEN_WIDTH * y) + i] = 0xFF000000;

        int textureOffsetX;
        // calculate textureOffsetX
        if (rays[i].wasHitVertical)
            // Perform offset for the vertical hit
            textureOffsetX = (int)rays[i].wallHitY % TILE_SIZE;
        else
            // perform offset for the horizontal hit
            textureOffsetX = (int)rays[i].wallHitX % TILE_SIZE;

        // get the correct texture id number from the map content
        int texNum = rays[i].wallHitContent - 1;

        // Render wall from top to bottom
        for (int y = wallTopPixel; y < wallBottomPixel; y++)
        {
            // Calculate textureOffset Y
            int distanceFromTop = y + (wallStripHeight / 2) - (SCREEN_HEIGHT / 2);            // fix distortion due to clamping values
            int textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT / wallStripHeight); // take into account that the size of the texture might have to be adjusted

            // Set the color of the wall based on the color from the texture in momory
            uint32_t texelColor = getTexture(texNum).texture_buffer[(TEXTURE_WIDTH * textureOffsetY) + textureOffsetX];
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

void clearColorBuffer(uint32_t *colorBuffer, uint32_t color)
{
    // Clear the entire color buffer with the color black
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            colorBuffer[(SCREEN_WIDTH * y) + x] = color;
        }
    }
}

void renderColorBuffer(SDL_Instance *instance, SDL_Texture *colorBufferTexture, uint32_t *colorBuffer)
{
    // copy all the texture information from the buffer
    SDL_UpdateTexture(
        colorBufferTexture,
        NULL,
        colorBuffer,
        (int)((uint32_t)SCREEN_WIDTH * sizeof(uint32_t)));
    SDL_RenderCopy(instance->renderer, colorBufferTexture, NULL, NULL);
}

void render(SDL_Instance *instance, SDL_Texture *colorBufferTexture, uint32_t *colorBuffer)
{
    SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
    SDL_RenderClear(instance->renderer);

    createWorld(colorBuffer);

    // render the color buffer from memory in real time
    renderColorBuffer(instance, colorBufferTexture, colorBuffer);
    // clear the color buffer
    clearColorBuffer(colorBuffer, 0xFF000000);

    // display the MiniMap
    renderMap(instance);
    renderRays(instance);
    renderPlayer(instance);

    SDL_RenderPresent(instance->renderer);
}

int main(int argc, char *argv[])
{
    SDL_Instance instance;
    uint32_t *colorBuffer = NULL;

    isGameRunning = initializeWindow(&instance);
    setup(&instance, &player, &colorBuffer);
    while (isGameRunning)
    {
        handleInputEvents();
        updateGame();
        render(&instance, colorBufferTexture, colorBuffer);
    }
    destroyWindow(&instance, colorBufferTexture, colorBuffer);
    return 0;
}