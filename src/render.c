#include "../include/init.h"

/**
* render - render the game
* @instance: SDL instance
* @player: player object
* @rays: rays object
* @map: map
* @colorBufferTexture: color buffer texture
* @colorBuffer: color buffer
*
* Return: void
*/
void render(SDL_Instance *instance,
	Player *player,
	Rays *rays,
	int map[MAP_NUM_ROWS][MAP_NUM_COLS],
	SDL_Texture *colorBufferTexture,
	uint32_t *colorBuffer)
{
	SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
	SDL_RenderClear(instance->renderer);

	/* Create the 3-D world*/
	createWorld(player, rays, colorBuffer);
	/* Render the color buffer from memory in real time */
	renderColorBuffer(instance, colorBufferTexture, colorBuffer);
	/* Clear the color buffer */
	clearColorBuffer(colorBuffer, 0xFF000000);

	/* Render game objects */
	renderMap(instance, map);
	renderRays(instance, player, rays);
	renderPlayer(instance, player);

	SDL_RenderPresent(instance->renderer);
}

/**
* renderMap - Render the map
* @instance: SDL instance
* @map: map
*
* Return: void
*/
void renderMap(SDL_Instance *instance, int map[MAP_NUM_ROWS][MAP_NUM_COLS])
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE;
			int tileY = i * TILE_SIZE;

			/* if the tile is a wall, color it white, otherwise color it 200 */
			int tileColor = map[i][j] != 0 ? 200 : 0;

			SDL_SetRenderDrawColor(instance->renderer,
				tileColor, tileColor, tileColor, 255);
			SDL_Rect mapTileRect = { tileX * MAP_SCALE_FACTOR,
				tileY * MAP_SCALE_FACTOR,
				TILE_SIZE * MAP_SCALE_FACTOR,
				TILE_SIZE * MAP_SCALE_FACTOR
			};
			SDL_RenderFillRect(instance->renderer, &mapTileRect);
		}
	}
}

/**
* renderRays - render the rays
* @instance: SDL instance
* @player: player object
* @rays: rays object
*
* Return: void
*/
void renderRays(SDL_Instance *instance, Player *player, Rays *rays)
{
	SDL_SetRenderDrawColor(instance->renderer, 255, 0, 0, 255);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		SDL_RenderDrawLine(
			instance->renderer,
			MAP_SCALE_FACTOR * player->x, /* Start position of ray */
			MAP_SCALE_FACTOR * player->y,
			MAP_SCALE_FACTOR * rays[i]->wallHitX, /* End position of ray */
			MAP_SCALE_FACTOR * rays[i]->wallHitY
		);
	}
}
