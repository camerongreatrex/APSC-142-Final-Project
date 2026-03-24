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
    // Iterate through both dimensions
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Print the current map at index x,y
            printc(map[y * width + x]);
            // If we reach the end of the iteration, print EMPTY
            if (x < width - 1) {
                printc(EMPTY);
            }
        }
        // New line after each map print
        printf("\n");
    }
}


void print_revealed_map(int player_y, int player_x) {
    // Clamp vertical range to map bounds so we don't print out-of-bounds rows
    int dy_min = -PLAYER_VISION_DISTANCE;
    if (player_y - PLAYER_VISION_DISTANCE < 0) {
        dy_min = -player_y;
    }
    int dy_max = PLAYER_VISION_DISTANCE;
    if (player_y + PLAYER_VISION_DISTANCE >= height) {
        dy_max = height - 1 - player_y;
    }

    // Clamp horizontal range to map bounds so we don't print out-of-bounds columns
    int dx_min = -PLAYER_VISION_DISTANCE;
    if (player_x - PLAYER_VISION_DISTANCE < 0) {
        dx_min = -player_x;
    }
    int dx_max = PLAYER_VISION_DISTANCE;
    if (player_x + PLAYER_VISION_DISTANCE >= width) {
        dx_max = width - 1 - player_x;
    }

    // Loop over each row in the vision window
    for (int dy = dy_min; dy <= dy_max; dy++) {
        // Loop over each column in the vision window
        for (int dx = dx_min; dx <= dx_max; dx++) {
            int y = player_y + dy;
            int x = player_x + dx;
            printc(map[y * width + x]);
            // Space between characters, matching print_map style
            if (dx < dx_max) {
                printc(EMPTY);
            }
        }
        printf("\n");
    }
}

int locate_character(char character, int *character_y, int *character_x) {
    // Attempt to find the character in the map and return a status code indicating
    // if they were present
    if (character_y == NULL || character_x == NULL) {
        return CHARACTER_NOT_FOUND;
    }
    
    // Iterate through all map coordinates until the character is found
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == character) {
                *character_y = y;
                *character_x = x;
                return FOUND_CHARACTER;
            }
        }
    }
    return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    // Try to open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    char *result = NULL;  // will grow with realloc
    int rows = 0;
    int cols = 0;

    // each line holds one row; symbols are every 3 characters
    char line[256] = {'0'};
    while (fgets(line, sizeof(line), file) != NULL) {
        // count symbols on this line (every 3rd character starting at index 0)
        int count = 0;
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i += 3) {
            count++;
        }
        if (rows == 0) {       // first row sets the width
            cols = count;
        }

        char *ptr = realloc(result, (rows + 1) * cols * sizeof(char));
        if (ptr == NULL) {
            free(result);
            fclose(file);
            return NULL;
        }
        result = ptr;

        // copy this row's symbols into the map
        for (int i = 0; i < cols; i++) {
            result[rows * cols + i] = line[i * 3];
        }

        rows++;
    }

    fclose(file);

    // if nothing was read, return NULL
    if (rows == 0 || cols == 0) {
        free(result);
        return NULL;
    }

    *map_height = rows;
    *map_width = cols;
    return result;
}
