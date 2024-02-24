#include "../include/init.h"

/**
* handleKeyPressedEvent - handle key down event
* @player: The player
* @isGameRunning: The game running status
* @key: The key pressed
*
* Return: void
*/
void handleKeyPressedEvent(Player *player, int *isGameRunning, int key)
{
	if (key == SDLK_ESCAPE)
		*isGameRunning = 0;
	if (key == SDLK_UP || key == SDLK_w)
		player->walkDirection = +1;
	if (key == SDLK_DOWN || key == SDLK_s)
		player->walkDirection = -1;
	if (key == SDLK_RIGHT || key == SDLK_d)
		player->turnDirection = +1;
	if (key == SDLK_LEFT || key == SDLK_a)
		player->turnDirection = -1;
}

/**
* handleKeyReleasedEvent - handle key up event
* @player: The player
* @key: The key released
*
* Return: void
*/
void handleKeyReleasedEvent(Player *player, int key)
{
	if (key == SDLK_UP || key == SDLK_w)
		player->walkDirection = 0;
	if (key == SDLK_DOWN || key == SDLK_s)
		player->walkDirection = 0;
	if (key == SDLK_RIGHT || key == SDLK_d)
		player->turnDirection = 0;
	if (key == SDLK_LEFT || key == SDLK_a)
		player->turnDirection = 0;
}

/**
* handleInputEvents - handle input events
* @player: The player
* @isGameRunning: The game running status
*
* Return: void
*/
void handleInputEvents(Player *player, int *isGameRunning)
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		*isGameRunning = 0;
		break;
	}
	case SDL_KEYDOWN:
	{
		handleKeyPressedEvent(player, isGameRunning, event.key.keysym.sym);
		break;
	}
	case SDL_KEYUP:
	{
		handleKeyReleasedEvent(player, event.key.keysym.sym);
		break;
	}
	default:
		break;
	}
}
