#include "../include/init.h"

/**
 * main - Entry point for the game
 * @argc: The number of command line arguments
 * @argv: The command line arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int __attribute__((unused)) argc, char __attribute__((unused)) * argv[])
{
    int isGameRunning = FALSE;
    SDL_Instance instance;
    Player player;

    isGameRunning = initialize_game(&instance);

    if (isGameRunning == FALSE)
    {
        fprintf(stderr, "Failed to initialize the game.\n");
        return (EXIT_FAILURE);
    }

    if (initialize_player(&player) == FALSE)
    {
        fprintf(stderr, "Error creating the player!\n");
        return (EXIT_FAILURE);
    }

    while (isGameRunning)
    {
        break;
    }

    destroy_game(&instance);
    return (EXIT_SUCCESS);
}