#include "../include/initialize.h"
#include "../include/player.h"
#include "../include/events.h"
#include "../include/game_map.h"
#include "../include/raycasting.h"

/**
 * main - Entry point for the game
 * @argc: The number of command line arguments
 * @argv: The command line arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    int isGameRunning = 0;
    SDL_Instance instance;
    Player player;
    Rays *rays = malloc(sizeof(Rays) * NUM_RAYS);

    if (rays == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for rays\n");
        return (EXIT_FAILURE);
    }

    const int map[MAP_NUMBER_ROWS][MAP_NUMBER_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    isGameRunning = initialize_game(&instance);

    if (isGameRunning != 0)
    {
        fprintf(stderr, "Failed to initialize the game.\n");
        return (EXIT_FAILURE);
    }

    if (initialize_player(&player) != 0)
    {
        fprintf(stderr, "Error creating the player!\n");
        return (EXIT_FAILURE);
    }

    while ("Maze game is running")
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
        SDL_RenderClear(instance.renderer);

        if (poll_game_events() != 0)
            break;
        draw_map(&instance, &map);
        render_player(&instance, &player);
        cast_all_rays(&player, rays, &map);
        renderRays(&instance, &player, rays);
        draw_rays(&instance, &player, rays);

        SDL_RenderPresent(instance.renderer);
    }
    if (rays != NULL)
        free(rays);
    destroy_game(&instance);
    return (EXIT_SUCCESS);
}