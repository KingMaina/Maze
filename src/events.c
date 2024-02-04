#include "../include/initialize.h"
#include "../include/events.h"

/**
 * poll_game_events - Polls for game events
 *
 * Return: 1 if the game is no longer running, 0 otherwise
*/
int poll_game_events(void)
{
    SDL_Event event;
    SDL_KeyboardEvent key;
    int exitGame = 0;

    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exitGame = 1;
                break;
            case SDL_KEYDOWN:
                key = event.key;
                if (key.keysym.sym == SDLK_ESCAPE)
                    exitGame = 1;
                break;
            default:
                break;
        }
    }
    return (exitGame);
}