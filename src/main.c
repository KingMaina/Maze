#include "../include/initialize.h"
#include "../include/player.h"
#include "../include/events.h"

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
        render_player(&instance, &player);

        SDL_RenderPresent(instance.renderer);
    }

    destroy_game(&instance);
    return (EXIT_SUCCESS);
}