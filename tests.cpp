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
TEST_CASE("move_character x and y are valid directions") {

    int y = 5;
    int x = 5;

    move_character(&y, &x, 1, -1);

    CHECK(y == 6);
    CHECK(x == 4);
}
// tests for charge_minotaur

// tests for locate character
TEST_CASE("locate_character finds player") {
    int y = 1;
    int x = 1;
    int result = locate_character(PLAYER, &y, &x);

    CHECK(result == FOUND_CHARACTER);
    CHECK(y >= 0);
    CHECK(x >= 0);
}

TEST_CASE("locate_character finds minotaur") {
    int y = 1;
    int x = 1;
    int result = locate_character(MINOTAUR, &y, &x);

    CHECK(result == FOUND_CHARACTER);
    CHECK(y >= 0);
    CHECK(x >= 0);
}

TEST_CASE("locate_character returns not found when missing") {
    int y = 1;
    int x = 1;
    int result = locate_character('Z', &y, &x);

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
