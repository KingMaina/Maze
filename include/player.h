#ifndef __PLAYER_H
#define __PLAYER_H

/**
 * struct Player - The player
 * @x: The x coordinate of the player
 * @y: The y coordinate of the player
 * @width: The width of the player
 * @height: The height of the player
 * @rotationAngle: The angle at which the player is facing
 * @turnDirection: -1 for left, +1 for right
 * @walkDirection: -1 for back, +1 for front
 * @walkSpeed: The speed at which the player walks
 * @turnSpeed: The speed at which the player turns
*/
typedef struct Player
{
    float x; /* The x coordinate of the player */
    float y; /* The y coordinate of the player */
    float width; /* The width of the player */
    float height; /* The height of the player */
    float rotationAngle; /* The angle at which the player is facing */
    int turnDirection; /* -1 for left, +1 for right */
    int walkDirection; /* -1 for back, +1 for front */
    float walkSpeed; /* The speed at which the player walks */
    float turnSpeed; /* The speed at which the player turns */
} Player; /* The player */

int render_player(SDL_Instance *, Player *);
int initialize_player(Player *);

#endif /* __PLAYER_H */
