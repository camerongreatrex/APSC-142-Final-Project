// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 10


extern char *map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case MINOTAUR:
            change_text_colour(MAGENTA);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

void print_map(void) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printc(map[y * width + x]);
            if (x < width - 1) {
                printc(EMPTY);  // plain space, no colour codes
            }
        }
        printf("\n");
    }
}


 void print_revealed_map(int player_y, int player_x) {
//     for (int dy = -PLAYER_VISION_DISTANCE; dy <= PLAYER_VISION_DISTANCE; dy++) {
//         for (int dx = -PLAYER_VISION_DISTANCE; dx <= PLAYER_VISION_DISTANCE; dx++) {
//             int y = player_y + dy;
//             int x = player_x + dx;
//             // Check bounds before printing map tile
//             if (y >= 0 && y < height && x >= 0 && x < width) {
//                 printc(map[y * width + x]);
//             } else {
//                 printc(EMPTY);
//             }
//         }
//         printf("\n");
//     }
 }

int locate_character(char character, int *character_y, int *character_x) {
//     // Attempt to find the character in the map and return a status code indicating
//     // if they were present
//
//     if (character_y == NULL || character_x == NULL) {
//         return CHARACTER_NOT_FOUND;
//     }
//     for (int x = 0; x < width; x++) {
//         for (int y = 0; y < height; y++) {
//             if (map[y * width + x] == character) {
//                 *character_y = y;
//                 *character_x = x;
//                 return FOUND_CHARACTER;
//             }
//         }
//     }
     return CHARACTER_NOT_FOUND;
 }


char *load_map(char *filename, int *map_height, int *map_width) {
    //implement in week 4 of project
    return NULL;
}
