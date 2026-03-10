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
