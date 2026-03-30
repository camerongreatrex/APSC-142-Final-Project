// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C" {
#include "defines.h"
#include "map.h"
#include "character.h"
#include "game.h"
char *map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* Tests for map.c */
TEST_SUITE_BEGIN("Map tests");
// Tests for print_map
TEST_CASE("print_map runs without crashing") {
    width = 3;
    height = 2;

    char test_map[] = {
        PLAYER, EMPTY, WALL,
        EMPTY, MINOTAUR, EMPTY
    };

    map = test_map;
    print_map();
    CHECK(true);
}

// Tests for load_map
TEST_CASE("load_map is empty") {
    int h, w;
    char *result = load_map(MAP_NAME, &h, &w);
    CHECK(result == NULL);
}

// Tests for load_map
TEST_CASE("load_map returns NULL when file does not exist (or cannot be opened)") {
    int h, w;
    char *result = load_map(MAP_NAME, &h, &w);   // "map.txt" does not exist in the test environment
    CHECK(result == NULL);
}

TEST_CASE("load_map successfully parses a valid map file (full success path)") {
    // Create a tiny valid map file on disk so we can test the entire loading logic
    char *temp_filename = "test_load_map.txt";

    FILE* f = fopen(temp_filename, "w");
    REQUIRE(f != NULL);

    // A 2-row × 3-col map
    fprintf(f, "W  P  W\n");
    fprintf(f, "W  M  W\n");
    fclose(f);

    int h = 0, w = 0;
    char* result = load_map(temp_filename, &h, &w);

    REQUIRE(result != NULL);        // file was read and parsed
    CHECK(h == 2);                  // correct number of rows
    CHECK(w == 3);                  // correct number of columns

    // Verify the data was copied correctly
    CHECK(result[0*3 + 0] == WALL);
    CHECK(result[0*3 + 1] == PLAYER);
    CHECK(result[0*3 + 2] == WALL);
    CHECK(result[1*3 + 0] == WALL);
    CHECK(result[1*3 + 1] == MINOTAUR);
    CHECK(result[1*3 + 2] == WALL);

    free(result);                   // must free what load_map allocated

    // Clean up the temporary file
    remove(temp_filename);
}
TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// tests for sees_player
TEST_CASE("sees_player returns CAUGHT_PLAYER when on same cell") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(2, 2, 2, 2) == CAUGHT_PLAYER);
}

TEST_CASE("sees_player returns RIGHT when player is to the right, no walls") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(2, 4, 2, 1) == RIGHT);
}

TEST_CASE("sees_player returns LEFT when player is to the left, no walls") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(2, 0, 2, 3) == LEFT);
}

TEST_CASE("sees_player returns DOWN when player is below, no walls") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(4, 2, 1, 2) == DOWN);
}

TEST_CASE("sees_player returns UP when player is above, no walls") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(0, 2, 3, 2) == UP);
}

TEST_CASE("sees_player returns SEES_NOTHING when wall is between (horizontal)") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = WALL;
    CHECK(sees_player(2, 4, 2, 0) == SEES_NOTHING);
}

TEST_CASE("sees_player returns SEES_NOTHING when wall is between (vertical)") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = WALL;
    CHECK(sees_player(0, 2, 4, 2) == SEES_NOTHING);
}

TEST_CASE("sees_player returns SEES_NOTHING when wall is between (left path)") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = WALL;
    CHECK(sees_player(2, 0, 2, 4) == SEES_NOTHING);
}

TEST_CASE("sees_player returns SEES_NOTHING when wall is between (down path)") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = WALL;
    CHECK(sees_player(4, 2, 0, 2) == SEES_NOTHING);
}

TEST_CASE("sees_player returns SEES_NOTHING when not same row or column") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(sees_player(0, 0, 3, 3) == SEES_NOTHING);
}

// tests for move_character
TEST_CASE("move_character moves left") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, LEFT, PLAYER) == MOVED_OKAY);
    CHECK(y == 2); CHECK(x == 1);
}

TEST_CASE("move_character moves right") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, RIGHT, PLAYER) == MOVED_OKAY);
    CHECK(y == 2); CHECK(x == 3);
}

TEST_CASE("move_character moves up") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, UP, PLAYER) == MOVED_OKAY);
    CHECK(y == 1); CHECK(x == 2);
}

TEST_CASE("move_character moves down") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, DOWN, PLAYER) == MOVED_OKAY);
    CHECK(y == 3); CHECK(x == 2);
}

TEST_CASE("move_character invalid direction") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, 'Z', PLAYER) == MOVED_INVALID_DIRECTION);
}

TEST_CASE("move_character blocked by wall") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 3] = WALL;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, RIGHT, PLAYER) == MOVED_WALL);
}

TEST_CASE("move_character moves into empty space") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(move_character(&y, &x, LEFT, PLAYER) == MOVED_OKAY);
    CHECK(x == 1);
}

TEST_CASE("move_character NULL pointers") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    CHECK(move_character(NULL, NULL, RIGHT, PLAYER) == MOVED_INVALID_DIRECTION);
}

TEST_CASE("move_character out of bounds") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 0, x = 0;
    CHECK(move_character(&y, &x, UP, PLAYER) == MOVED_WALL);
}

// tests for charge_minotaur
TEST_CASE("charge_minotaur moves 2 steps with no wall") {
    width = 7; height = 5;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[2 * 7 + 2] = MINOTAUR;
    int y = 2, x = 2;
    CHECK(charge_minotaur(&y, &x, 2, 6, RIGHT) == MOVED_OKAY);
    CHECK(y == 2); CHECK(x == 4);
    CHECK(test_map[2 * 7 + 2] == EMPTY);
    CHECK(test_map[2 * 7 + 4] == MINOTAUR);
}

TEST_CASE("charge_minotaur smashes through wall and returns MOVED_WALL") {
    width = 7; height = 5;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[2 * 7 + 2] = MINOTAUR;
    test_map[2 * 7 + 3] = WALL;
    int y = 2, x = 2;
    CHECK(charge_minotaur(&y, &x, 2, 6, RIGHT) == MOVED_WALL);
    CHECK(y == 2); CHECK(x == 3);
    CHECK(test_map[2 * 7 + 3] == MINOTAUR);
}

TEST_CASE("charge_minotaur returns CAUGHT_PLAYER when minotaur reaches player") {
    width = 7; height = 5;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[2 * 7 + 1] = MINOTAUR;
    test_map[2 * 7 + 3] = PLAYER;
    int y = 2, x = 1;
    CHECK(charge_minotaur(&y, &x, 2, 3, RIGHT) == CAUGHT_PLAYER);
}

TEST_CASE("charge_minotaur smashes wall going LEFT") {
    width = 7; height = 5;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[2 * 7 + 4] = MINOTAUR;
    test_map[2 * 7 + 3] = WALL;
    int y = 2, x = 4;
    CHECK(charge_minotaur(&y, &x, 2, 0, LEFT) == MOVED_WALL);
    CHECK(y == 2); CHECK(x == 3);
    CHECK(test_map[2 * 7 + 3] == MINOTAUR);
}

TEST_CASE("charge_minotaur smashes wall going UP") {
    width = 5; height = 7;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[4 * 5 + 2] = MINOTAUR;
    test_map[3 * 5 + 2] = WALL;
    int y = 4, x = 2;
    CHECK(charge_minotaur(&y, &x, 0, 2, UP) == MOVED_WALL);
    CHECK(y == 3); CHECK(x == 2);
    CHECK(test_map[3 * 5 + 2] == MINOTAUR);
}

TEST_CASE("charge_minotaur smashes wall going DOWN") {
    width = 5; height = 7;
    char test_map[35] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = MINOTAUR;
    test_map[3 * 5 + 2] = WALL;
    int y = 2, x = 2;
    CHECK(charge_minotaur(&y, &x, 6, 2, DOWN) == MOVED_WALL);
    CHECK(y == 3); CHECK(x == 2);
    CHECK(test_map[3 * 5 + 2] == MINOTAUR);
}

TEST_CASE("charge_minotaur returns MOVED_INVALID_DIRECTION for bad direction") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 2, x = 2;
    CHECK(charge_minotaur(&y, &x, 2, 4, 'Z') == MOVED_INVALID_DIRECTION);
}


// tests for locate character
TEST_CASE("locate_character finds player") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[2 * 5 + 2] = PLAYER;
    int y = -1, x = -1;
    CHECK(locate_character(PLAYER, &y, &x) == FOUND_CHARACTER);
    CHECK(y == 2); CHECK(x == 2);
}

TEST_CASE("locate_character finds minotaur") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    test_map[3 * 5 + 1] = MINOTAUR;
    int y = -1, x = -1;
    CHECK(locate_character(MINOTAUR, &y, &x) == FOUND_CHARACTER);
    CHECK(y == 3); CHECK(x == 1);
}

TEST_CASE("locate_character not found") {
    width = 5; height = 5;
    char test_map[25] = {EMPTY};
    map = test_map;
    int y = 0, x = 0;
    CHECK(locate_character('Z', &y, &x) == CHARACTER_NOT_FOUND);
}

TEST_CASE("locate_character NULL pointers") {
    CHECK(locate_character(PLAYER, NULL, NULL) == CHARACTER_NOT_FOUND);
}

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("check_win continues when player inside map") {
    width = 10;
    height = 10;
    CHECK(check_win(5,5) == KEEP_GOING);
}

TEST_CASE("check_win when player reaches top outer wall") {
    width = 10;
    height = 10;
    CHECK(check_win(0,5) == YOU_WIN);
}

TEST_CASE("check_win when player reaches left outer wall") {
    width = 10;
    height = 10;
    CHECK(check_win(5,0) == YOU_WIN);
}

TEST_CASE("check_win when player goes past bottom boundary") {
    width = 10;
    height = 10;
    CHECK(check_win(10,5) == YOU_WIN);
}

TEST_CASE("check_win when player goes past right boundary") {
    width = 10;
    height = 10;
    CHECK(check_win(5,10) == YOU_WIN);
}

// tests for check_loss
TEST_CASE("check_loss detects player caught") {
    CHECK(check_loss(5,5,5,5) == YOU_LOSE);
}

TEST_CASE("check_loss continues when player not caught") {
    CHECK(check_loss(5,5,4,5) == KEEP_GOING);
}

TEST_SUITE_END();
