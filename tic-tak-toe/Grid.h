#pragma once

#include <iostream>
#include <string>

#define GRID_BOUND 3

enum Space : short {
    X,
    O,
    BLANK
};

class Grid {
    Space spaces[GRID_BOUND][GRID_BOUND];

    char spaceChar(int x, int y);

public:
    Grid();

    void printGrid();
    void printPlayerWin(Space player);
    void setSpace(int x, int y, Space type);
    void setSpace(char choice, Space type);
    bool gameOver();
    char spaceName(Space type);
};
