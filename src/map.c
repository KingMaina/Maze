#include "../include/game_map.h"

const int map[MAP_NUMBER_ROWS][MAP_NUMBER_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

/**
 * draw_map - Renders the map
 * @instance: The SDL instance
 *
 * Return: 0 if successful, 1 otherwise
 */
int draw_map(SDL_Instance *instance)
{
    int row = 0, column = 0;
    int success = 0;

    for (row = 0; row < MAP_NUMBER_ROWS; ++row)
    {
        for (column = 0; column < MAP_NUMBER_COLS; ++column)
        {
            int tileXCoordinate = column * TILE_SIZE;
            int tileYCoordinate = row * TILE_SIZE;
            int tileColor = map[row][column];

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