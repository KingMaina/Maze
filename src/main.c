#include "headers/init.h"
#include "headers/constants.h"

/**
 * main - Entry point for the game
 * @argc: The number of command line arguments
 * @argv: The command line arguments
 *
 * Return: 0 on success, 1 on failure 
*/
int main(int argc, char *argv[])
{
    int isGameRunning = FALSE;
    SDL_Instance instance;

    isGameRunning = initialize_game(&instance);

    if (isGameRunning == FALSE)
    {
        fprintf(stderr, "Failed to initialize the game.\n");
        return (EXIT_FAILURE);
    }
}