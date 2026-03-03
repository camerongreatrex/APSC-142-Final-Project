// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"

#include <stddef.h>

extern char *map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check to see if the Minotaur has caught the player
    // check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, they can't see
    // if one of them is the same, check if the path in between is clear
    // if the Minotaur can see the player, return the direction they must look (LEFT, RIGHT, UP, DOWN
    if (player_x == minotaur_x && player_y == minotaur_y) {
        return CAUGHT_PLAYER;
    }

    // Same row (horizontal check)
    if (player_y == minotaur_y) {
        // Player is to the RIGHT
        if (player_x > minotaur_x) {
            // Check from minotaur_x + 1 all the way to player_x value to see if there's a wall
            for (int x = minotaur_x + 1; x < player_x; x++) {
                // If the checked x value is a wall then the minotaur automatically can't see the player
                if (map[minotaur_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Since the minotaur can see the player and it's to the right of the minotaur, the minotaur
            // must move to the right
            return RIGHT;
        }

        // Player is to the LEFT - same logic as above
        if (player_x < minotaur_x) {
            for (int x = minotaur_x - 1; x > player_x; x--) {
                if (map[minotaur_y * width + x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return LEFT;
        }
    }

    // Same column (vertical check)
    if (player_x == minotaur_x) {
        // Player is DOWN
        if (player_y > minotaur_y) {
            // Check from minotaur_y + 1 all the way to player_y value to see if there's a wall
            for (int y = minotaur_y + 1; y < player_y; y++) {
                // If the checked y value is a wall then the minotaur automatically can't see the player
                if (map[y * width + minotaur_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            // Since the minotaur can see the player and it's below of the minotaur, the minotaur
            // must move down
            return DOWN;
        }

        // Player is UP - same logic as above
        if (player_y < minotaur_y) {
            for (int y = minotaur_y - 1; y > player_y; y--) {
                if (map[y * width + minotaur_x] == WALL) {
                    return SEES_NOTHING;
                }
            }
            return UP;
        }
    }
    return SEES_NOTHING;
}

int move_character(int *y, int *x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wall
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers

    if (y == NULL || x == NULL) {
        return MOVED_INVALID_DIRECTION;
    }

    // Check invalid direction
    if (direction != LEFT && direction != RIGHT &&
        direction != UP && direction != DOWN) {
        return MOVED_INVALID_DIRECTION;
    }

    int new_y = *y;
    int new_x = *x;

    // Calculate new position
    if (direction == LEFT) {
        new_x--;
    } else if (direction == RIGHT) {
        new_x++;
    } else if (direction == UP) {
        new_y--;
    } else if (direction == DOWN) {
        new_y++;
    }

    // Check bounds
    if (new_x < 0 || new_x >= width ||
        new_y < 0 || new_y >= height) {
        return MOVED_WALL;
    }

    // Check if new position is a wall
    if (map[new_y * width + new_x] == WALL) {
        return MOVED_WALL;
    }
    // Move is valid — update map
    map[*y * width + *x] = EMPTY; // clear old spot
    map[new_y * width + new_x] = character; // place character

    // Update coordinates
    *y = new_y;
    *x = new_x;

    return MOVED_OKAY;
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates

    return MOVED_OKAY;
}
