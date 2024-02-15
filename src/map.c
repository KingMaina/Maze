#include "../include/game_map.h"
#include "../include/constants.h"
#include "../include/player.h"
#include "../include/initialize.h"
#include "../include/raycasting.h"


/**
 * draw_map - Renders the map
 * @instance: The SDL instance
 *
 * Return: 0 if successful, 1 otherwise
 */
int draw_map(SDL_Instance *instance, const int (*map)[MAP_NUMBER_ROWS][MAP_NUMBER_COLS])
{
    int row = 0, column = 0;
    int success = 0;

    for (row = 0; row < MAP_NUMBER_ROWS; ++row)
    {
        for (column = 0; column < MAP_NUMBER_COLS; ++column)
        {
            int tileXCoordinate = column * TILE_SIZE;
            int tileYCoordinate = row * TILE_SIZE;
            int tileColor = (*map)[row][column];

            if (tileColor != 0)
                tileColor = 150;
            else
                tileColor = 0;
            SDL_SetRenderDrawColor(
                instance->renderer,
                tileColor,
                tileColor,
                tileColor,
                0xFF);
            SDL_Rect mapTile = {
                tileXCoordinate * MAP_SCALE_FACTOR,
                tileYCoordinate * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR};
            SDL_RenderFillRect(
                instance->renderer,
                &mapTile);
        }
    }
    return (success);
}

void renderRays(SDL_Instance *instance, Player *player, Rays rays[NUM_RAYS]){
    SDL_SetRenderDrawColor(instance->renderer, 0,255,0,255);
    for (int i = 0; i < NUM_RAYS; i++){
        SDL_RenderDrawLine(
            instance->renderer,
            MAP_SCALE_FACTOR * player->x,            // start position of ray
            MAP_SCALE_FACTOR * player->y,
            MAP_SCALE_FACTOR * rays[i]->wallSideHitX,    // end position of ray
            MAP_SCALE_FACTOR * rays[i]->wallSideHitY
        );
    }
}