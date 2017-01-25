#include "Grid.h"

#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

Grid::Grid() {
    for (int i = 0; i < GRID_BOUND; i++) {
        for (int j = 0; j < GRID_BOUND; j++) {
            spaces[i][j] = BLANK;
        }
    }
}

void Grid::printGrid() {
    // lazy print
    for (int i = 0; i < GRID_BOUND; i++) {
        for (int j = 0; j < GRID_BOUND; j++) {
            if (spaces[i][j] == X) {
                printf(ANSI_COLOR_GREEN);
            }
            else if (spaces[i][j] == O) {
                printf(ANSI_COLOR_CYAN);
            }
            else {
                printf(ANSI_COLOR_RED);
            }
            printf(" %c ", spaceChar(i, j));
            printf(ANSI_COLOR_RESET);
        }
        printf("\n");
    }
    printf("\n");
}

void Grid::printPlayerWin(Space player) {
    printf("Player %c wins!\n", spaceName(player));
}

void Grid::setSpace(int x, int y, Space type) {
    if (x >= GRID_BOUND ||
        y >= GRID_BOUND ||
        spaces[x][y] != BLANK)
    {
        throw "Error: Invalid location choice!";
    }
    spaces[x][y] = type;
}

void Grid::setSpace(char choice, Space type) {
    if (choice < 'A' || choice > ('A' + (GRID_BOUND * GRID_BOUND) - 1)) {
        throw "Error: Invalid grid location!";
    }
    int pos = (int)(choice - 'A');

    int y = pos % GRID_BOUND,
        x = (pos - y) / GRID_BOUND;
    setSpace(x, y, type);
}

char Grid::spaceChar(int x, int y) {
    switch (spaces[x][y]) {
        case X:
            return spaceName(X);
        case O:
            return spaceName(O);
        case BLANK:
            return ('A' + y + (x * GRID_BOUND));
    }
}

char Grid::spaceName(Space type) {
    switch (type) {
        case X:
            return 'X';
        case O:
            return 'O';
        case BLANK:
            return ' ';
    }
}

bool Grid::gameOver() {
    Space last_hor = spaces[0][0],
          last_ver = last_hor;

    int hor_counter = 0,
        ver_counter = 0;

    for(int i = 0; i < GRID_BOUND; i++) {
        last_hor = spaces[i][0];
        for (int j = 1; j < GRID_BOUND; j++) {
            if (last_hor == spaces[i][j] &&
                last_hor != BLANK) {
                hor_counter++;
            }
            else {
                break;
            }
        }
        if (hor_counter == 2) {
            printPlayerWin(last_hor);
            return true;
        }
        hor_counter = 0;
    }
    for(int j = 0; j < GRID_BOUND; j++) {
        last_ver = spaces[0][j];
        for (int i = 1; i < GRID_BOUND; i++) {
            if (last_ver == spaces[i][j] &&
                last_ver != BLANK) {
                ver_counter++;
            }
            else {
                break;
            }
        }
        if (ver_counter == 2) {
            printPlayerWin(last_ver);
            return true;
        }
        ver_counter = 0;
    }
    if (spaces[1][1] != BLANK &&
        ((spaces[0][0] == spaces[1][1] &&
          spaces[2][2] == spaces[1][1])
        ||
         (spaces[0][2] == spaces[1][1] &&
          spaces[2][0] == spaces[1][1]))) {
            printPlayerWin(spaces[1][1]);
            return true;
        }
    return false;
}
