#include "../include/initialize.h"
#include "../include/player.h"
#include "../include/constants.h"

/**
 * initialize_player - Initializes the player
 * @player: A pointer to the player
 *
 * Return: 0 on success, 1 on failure
*/
int initialize_player(Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "No player found!");
        return (1);
    }
    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;
    player->width = 1;
    player->height = 1;
    return (0);
}

/**
 * render_player - Renders the player
 * @renderer: The game renderer
 * @player: A pointer to the player
 * 
 * Return: 0 on success, 1 on failure
*/
int render_player(SDL_Instance *instance, Player *player)
{
    SDL_SetRenderDrawColor(instance->renderer, 255,255,255,255);

    if (instance->renderer == NULL)
    {
        fprintf(stderr, "No renderer or player found!");
        return (1);
    }
    SDL_Rect playerRect = {player->x * 0.25, player->y * 0.25, player->width * 0.25, player->height * 0.25};

    SDL_RenderFillRect(instance->renderer, &playerRect);
    return (0);
}