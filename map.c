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
                printc(EMPTY); // plain space, no colour codes
            }
        }
        printf("\n");
    }
}


void print_revealed_map(int player_y, int player_x) {
    for (int dy = -PLAYER_VISION_DISTANCE; dy <= PLAYER_VISION_DISTANCE; dy++) {
        for (int dx = -PLAYER_VISION_DISTANCE; dx <= PLAYER_VISION_DISTANCE; dx++) {
            int y = player_y + dy;
            int x = player_x + dx;
            // Check bounds before printing map tile
            if (y >= 0 && y < height && x >= 0 && x < width) {
                printc(map[y * width + x]);
            } else {
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
    char *loaded_map = NULL;  // will grow with realloc
    int rows = 0;
    int cols = 0;

    // buffer big enough for one line, each symbol takes 3 chars (symbol + 2 spaces)
    // buffer handles any  map width
    char line_buffer[256] = {'0'};
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        // count symbols on this line (every 3rd character starting at index 0)
        int line_cols = 0;
        for (int i = 0; line_buffer[i] != '\0' && line_buffer[i] != '\n'; i += 3) {
            line_cols++;
        }
        if (rows == 0) {       // first row sets the width
            cols = line_cols;
        }

        char *temp = realloc(loaded_map, (rows + 1) * cols * sizeof(char));
        if (temp == NULL) {
            free(loaded_map);
            fclose(file);
            return NULL;
        }
        loaded_map = temp;

        // copy this row's symbols into the map
        for (int i = 0; i < cols; i++) {
            loaded_map[rows * cols + i] = line_buffer[i * 3];
        }

        rows++;
    }

    fclose(file);

    // if nothing was read, return NULL
    if (rows == 0 || cols == 0) {
        free(loaded_map);
        return NULL;
    }

    *map_height = rows;
    *map_width = cols;
    return loaded_map;
}
