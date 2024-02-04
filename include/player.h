#ifndef __PLAYER_H
#define __PLAYER_H

/**
 * Player - The player
 * @x: The x coordinate of the player
 * @y: The y coordinate of the player
 * @width: The width of the player
 * @height: The height of the player
*/
typedef struct Player
{
    float x;
    float y;
    float width;
    float height;
} Player;

int initialize_player(Player *);

#endif /* __PLAYER_H */