#ifndef INIT_H_
#define INIT_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <float.h>

/* Custom header files */
#include "./constants.h"

/**
* struct SDL_Instance - SDL instance
* @window: SDL window
* @renderer: SDL renderer
*
* Description: SDL instance
*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
* struct Player - struct to hold the player object
* @x: x-coordinate of the player
* @y: y-coordinate of the player
* @width: width of the player
* @height: height of the player
* @turnDirection: direction of the player
* @walkDirection: direction of the player
* @rotationAngle: angle of the player
* @walkSpeed: speed of the player
* @turnSpeed: speed of the player
*/
typedef struct Player
{
	float x; /* x-coordinate of the player */
	float y; /* y-coordinate of the player */
	float width; /* width of the player */
	float height; /* height of the player */
	int turnDirection; /* -1 for left, +1 for right */
	int walkDirection; /* -1 for back, +1 for forward */
	float rotationAngle; /* in radians */
	float walkSpeed; /* pixels per second */
	float turnSpeed; /* angles per second */

} Player;

/**
* struct Ray - struct to hold the ray object
* @rayAngle: angle of the ray
* @wallHitX: x-coordinate of the wall hit
* @wallHitY: y-coordinate of the wall hit
* @distance: distance of the wall hit
* @wasHitVertical: if the wall was hit vertically
* @isRayFacingUpward: if the ray is facing upward
* @isRayFacingDownward: if the ray is facing downward
* @isRayFacingLeft: if the ray is facing left
* @isRayFacingRight: if the ray is facing right
* @wallHitContent: content of the wall hit
*/
typedef struct Ray
{
	float rayAngle; /* angle of the ray */
	float wallHitX; /* x-coordinate of the wall hit */
	float wallHitY; /* y-coordinate of the wall hit */
	float distance; /* distance of the wall hit */
	int wasHitVertical; /* if the wall was hit vertically */
	int isRayFacingUpward; /* if the ray is facing upward */
	int isRayFacingDownward; /* if the ray is facing downward */
	int isRayFacingLeft; /* if the ray is facing left */
	int isRayFacingRight; /* if the ray is facing right */
	int wallHitContent; /* content of the wall hit */
} Rays[NUM_RAYS];

/* Game setup functions */
int initializeWindow(SDL_Instance *instance);
void setup(SDL_Instance *instance, Player *player, uint32_t **colorBuffer);
void createWorld(Player *player, Rays *rays, uint32_t *colorBuffer);

/* Event handling functions */
void handleInputEvents(Player *player, int *isGameRunning);
void handleKeyPressedEvent(Player *player, int *isGameRunning, int key);
void handleKeyReleasedEvent(Player *player, int key);
void updateGame(Player *player, Rays rays[],
	int map[MAP_NUM_ROWS][MAP_NUM_COLS], int *ticksLastFrame);

/* Player functions */
void movePlayer(Player *player, int map[MAP_NUM_ROWS][MAP_NUM_COLS],
	float deltaTime);
void renderPlayer(SDL_Instance *instance, Player *player);

/* Raycasting functions */
void castRay(Player *player, Rays *rays, int map[MAP_NUM_ROWS][MAP_NUM_COLS],
	float rayAngle, int stripId);
void castAllRays(Player *player, Rays rays[],
	int map[MAP_NUM_ROWS][MAP_NUM_COLS]);

/* Rendering functions */
void renderMap(SDL_Instance *instance, int map[MAP_NUM_ROWS][MAP_NUM_COLS]);
void renderRays(SDL_Instance *instance, Player *player, Rays *rays);
void renderColorBuffer(SDL_Instance *instance,
	SDL_Texture *colorBufferTexture, uint32_t *colorBuffer);
void render(SDL_Instance *instance, Player *player,
	Rays *rays, int map[MAP_NUM_ROWS][MAP_NUM_COLS],
	SDL_Texture *colorBufferTexture, uint32_t *colorBuffer);

/* free memory functions */
void freeMemory(SDL_Instance *instance, SDL_Texture *, uint32_t *);
void clearColorBuffer(uint32_t *colorBuffer, uint32_t color);

/* Helper functions */
float normaliseAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
int mapHasWallAt(int map[MAP_NUM_ROWS][MAP_NUM_COLS], float x, float y);

#endif /* INIT_H_ */
