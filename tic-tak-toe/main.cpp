#include <iostream>

#include "Grid.h"

void playGame(Grid g);

int main (int argc, char **argv) {
    Grid ttt;

    ttt.printGrid();

    playGame(ttt);
}

void playGame(Grid g) {
    Space players[] = { X,O };
    char input, c;
    int player = 0, moves = 0;
    while(!g.gameOver() && moves < 9) {
        printf("Player %c: Enter a placement: ", g.spaceName(players[player]));

        scanf("%c", &input);
        scanf("%c", &c); // catch newline
        if (input >= 'a' && input <= 'z') {
            input -= 32;
        }
        if (input == '\n') { }
        else {
            bool success = true;
            try {
                g.setSpace(input, players[player]);
            }
            catch (const char *error) {
                printf("%s\n", error);
                printf("Please try again\n");
                success = false;
            }
            if (success) {
                g.printGrid();
                player = player ? 0 : 1;
                moves ++;
            }
        }
    }
    if (moves >= 9) {
        printf("Tie game!\n");
    }
}
