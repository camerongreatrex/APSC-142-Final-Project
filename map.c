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
    // Open the map.txt file
    FILE *fileMap = fopen("map.txt", "r");
    // if the file is empty
    if (fileMap == NULL || fgetc(fileMap) == EOF) {
        printf("Error opening map file\n");
    } else {
        char c;
        while ((c = fgetc(fileMap)) != EOF) {
            printc(c);
        }
    }
    fclose(fileMap);
}


void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
}

int locate_character(int* character_y, int* character_x, char character) {
    // Attempt to find the character in the map and return a status code indicating
    // if they were present
    return FOUND_CHARACTER;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    //implement in week 4 of project
    return NULL;
}
