#include "../include/initialize.h"
#include "../include/player.h"
#include "../include/constants.h"
#include "../include/game_map.h"

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
    player->rotationAngle = M_PI / 2;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->walkSpeed = 100;
    player->turnSpeed = 45 * (M_PI / 180);
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
    if (instance->renderer == NULL)
    {
        fprintf(stderr, "No renderer or player found!");
        return (1);
    }
    SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);

    SDL_Rect playerRect = {
        player->x * MAP_SCALE_FACTOR,
        player->y * MAP_SCALE_FACTOR,
        player->width * MAP_SCALE_FACTOR,
        player->height * MAP_SCALE_FACTOR};

    SDL_RenderFillRect(instance->renderer, &playerRect);
    SDL_RenderDrawLine(
        instance->renderer,
        MAP_SCALE_FACTOR * player->x,
        MAP_SCALE_FACTOR * player->y,
        MAP_SCALE_FACTOR * player->x + cos(player->rotationAngle) * 40,
        MAP_SCALE_FACTOR * player->y + sin(player->rotationAngle) * 40);
    return (0);
}
