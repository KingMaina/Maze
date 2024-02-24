#include "../include/init.h"
#include "../include/constants.h"
#include "../include/textures.h"

SDL_Texture *colorBufferTexture;

/**
* setup - setup the game
* @instance: SDL instance
* @player: player object
* @colorBuffer: color buffer
*
* Return: void
*/
void setup(SDL_Instance *instance, Player *player, uint32_t **colorBuffer)
{
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	player->width = 1;
	player->height = 1;
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->rotationAngle = PI / 2;
	player->walkSpeed = 100;
	player->turnSpeed = 45 * (PI / 180);

	/* Allocate enough memory to hold the entire screen in the color buffer */
	uint32_t buffSize = SCREEN_WIDTH * SCREEN_HEIGHT * 8;
	*colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * buffSize);

	/* Create a SDL_Texture to display the color buffer */
	colorBufferTexture = SDL_CreateTexture(
		instance->renderer,          /* create textures to renderer */
		SDL_PIXELFORMAT_RGBA32,      /* pixel format -> alpha RGB fill */
		SDL_TEXTUREACCESS_STREAMING, /* FLAG -> able to change texture, real time */
		SCREEN_WIDTH,                /* size */
		SCREEN_HEIGHT                /* size */
	);

	/* Decode all png files and load the wallTextures array */
	loadWallTextures();
}

/**
* updateGame - update the game
* @player: player object
* @rays: rays object
* @map: map
* @ticksLastFrame: last frame time in milliseconds
*
* Return: void
*/
void updateGame(Player *player, Rays rays[],
	int map[MAP_NUM_ROWS][MAP_NUM_COLS], int *ticksLastFrame)
{
	/* delay some time until the target frame time length is reached */
	/* http://wiki.libsdl.org/SDL2/SDL_Delay */

	/* Compute how long before the target frame time in milliseconds is reached */
	int timeToWait = FRAME_TIME_LENGHT - (SDL_GetTicks() - *ticksLastFrame);

	/* Only delay execution if program is running too fast */
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGHT)
	{
		SDL_Delay(timeToWait);
	}
	/* Delta time to be used as an update factor when changing game objects */
	float deltaTime = (SDL_GetTicks() - *ticksLastFrame) / 1000.0f;

	/* Store the milliseconds of the current frame to be used in the future */
	*ticksLastFrame = SDL_GetTicks();

	movePlayer(player, map, deltaTime);
	castAllRays(player, rays, map);
}

/**
* main - Initialize the game and start the game loop
* @argc: number of arguments passed to the program
* @argv: array of arguments passed to the program
*
* Return: 0 on success, 1 on failure
*/
int main(int argc, char *argv[])
{
	SDL_Instance instance;
	Player player;
	Rays *rays = malloc(sizeof(Rays) * (sizeof(char) * NUM_RAYS));
	/* SDL_Texture *colorBufferTexture; */
	uint32_t *colorBuffer = NULL;
	int isGameRunning = 0;
	int ticksLastFrame = 0;
	int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {

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

	isGameRunning = initializeWindow(&instance);
	setup(&instance, &player, &colorBuffer);
	while (isGameRunning)
	{
		handleInputEvents(&player, &isGameRunning);
		updateGame(&player, rays, map, &ticksLastFrame);
		render(&instance, &player, rays, map, colorBufferTexture, colorBuffer);
	}
	freeMemory(&instance, colorBufferTexture, colorBuffer);
	free(rays);
	return (0);
}
