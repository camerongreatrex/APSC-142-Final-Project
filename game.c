// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "game.h"

#include <stdio.h>

extern char * map;
extern int height;
extern int width;

int check_win(int player_y, int player_x) {
    // The player wins if they escape the map boundaries (i.e., they are in a place an outer wall tile should be).

    // If player is on outer boundary tile
    if (player_y == 0 || player_y == height - 1 ||
        player_x == 0 || player_x == width - 1) {
        printf("Congrats you win!\n");
        return YOU_WIN;
        }

    return KEEP_GOING;
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // The player loses if they are caught by the Minotaur
    if (player_x == minotaur_x && player_y == minotaur_y) {
        printf("You lose! Better luck next time!\n");
        return YOU_LOSE;
    }
    return KEEP_GOING;
}

