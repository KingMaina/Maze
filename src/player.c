#include "../include/init.h"

int initialize_player(Player *player)
{
    if (player == NULL)
    {
        fprintf(stderr, "No player found!");
        return (FALSE);
    }
    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;
    player->width = 1;
    player->height = 1;
    return (TRUE);
}