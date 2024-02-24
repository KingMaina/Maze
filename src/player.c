#include "../include/init.h"

/**
* movePlayer - move the player
* @player: player object
* @map: Game map
* @deltaTime: time between frames
*
* Return: void
*/
void movePlayer(Player *player, int map[MAP_NUM_ROWS][MAP_NUM_COLS],
float deltaTime)
{
	float newRotAngle = player->turnDirection * player->turnSpeed * deltaTime;

	player->rotationAngle += newRotAngle;
	float moveStep = player->walkDirection * player->walkSpeed * deltaTime;
	float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
	float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

	/* perform wall colision */
	/* Only assign newPlayer position when not overlapping wall position */
	if (!mapHasWallAt(map, newPlayerX, newPlayerY))
	{
		player->x = newPlayerX;
		player->y = newPlayerY;
	}
}

/**
* renderPlayer - render the player
* @instance: SDL_Instance object
* @player: player object
*
* Return: void
*/
void renderPlayer(SDL_Instance *instance, Player *player)
{
	SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);

	/* Draw a square for the player */
	SDL_Rect playerRect = {
		player->x * MAP_SCALE_FACTOR,
		player->y * MAP_SCALE_FACTOR,
		player->width * MAP_SCALE_FACTOR,
		player->height * MAP_SCALE_FACTOR};
	SDL_RenderFillRect(instance->renderer, &playerRect);

	/* Draw a line in the direction the player is facing */
	SDL_RenderDrawLine(
		instance->renderer,
		MAP_SCALE_FACTOR * player->x,
		MAP_SCALE_FACTOR * player->y,
		MAP_SCALE_FACTOR * player->x + cos(player->rotationAngle) * 40,
		MAP_SCALE_FACTOR * player->y + sin(player->rotationAngle) * 40);
}
