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
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// tests for sees_player

// tests for move_character
TEST_CASE("move_character moves correctly") {
    int y = 5;
    int x = 5;
    map[y * width + x] = PLAYER;
    map[y * width + (x + 1)] = EMPTY;
    move_character(&y, &x, RIGHT, PLAYER);

    CHECK(y == 5);
    CHECK(x == 6);
}

TEST_CASE("move_character invalid direction") {
    int y = 5;
    int x = 5;
    int result = move_character(&y, &x, 'Z', PLAYER);

    CHECK(result == MOVED_INVALID_DIRECTION);
}

TEST_CASE("move_character blocked by wall") {
    int y = 5;
    int x = 5;
    map[y * width + x] = PLAYER;
    map[y * width + (x + 1)] = WALL;
    int result = move_character(&y, &x, RIGHT, PLAYER);

    CHECK(result == MOVED_WALL);
}

TEST_CASE("move_character moves into empty space") {
    int y = 3;
    int x = 3;
    map[y * width + x] = PLAYER;
    map[y * width + (x - 1)] = EMPTY;
    int result = move_character(&y, &x, LEFT, PLAYER);

    CHECK(result == MOVED_OKAY);
    CHECK(x == 2);
}

// tests for charge_minotaur

// tests for locate character
TEST_CASE("locate_character finds player") {
    map[4 * width + 4] = PLAYER;
    int y = -1;
    int x = -1;
    int result = locate_character(PLAYER, &y, &x);

    CHECK(result == FOUND_CHARACTER);
    CHECK(y == 4);
    CHECK(x == 4);
}

TEST_CASE("locate_character finds minotaur") {
    map[7 * width + 2] = MINOTAUR;
    int y = -1;
    int x = -1;
    int result = locate_character(MINOTAUR, &y, &x);

    CHECK(result == FOUND_CHARACTER);
    CHECK(y == 7);
    CHECK(x == 2);
}

TEST_CASE("locate_character returns not found when missing") {
    int y = 0;
    int x = 0;
    int result = locate_character('Z', &y, &x);

    CHECK(result == CHARACTER_NOT_FOUND);
}

TEST_CASE("locate_character handles NULL pointers") {
    int result = locate_character(PLAYER, NULL, NULL);
    CHECK(result == CHARACTER_NOT_FOUND);
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
