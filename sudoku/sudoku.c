#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define NUM_DIGITS 9
#define NUM_ROWS   NUM_DIGITS
#define NUM_COLS   NUM_DIGITS
#define NUM_PEERS  20
#define NUM_UNITS  3
#define DIGITS     "123456789"
#define ROW_NAMES  "ABCDEFGHI"
#define COL_NAMES  DIGITS

typedef struct square {
  char vals[NUM_DIGITS+1]; // string of possible values
  unsigned char row;
  unsigned char col;
  struct square *peers[NUM_PEERS];
  struct square *units[NUM_UNITS][NUM_DIGITS];
} square_t;

typedef struct puzzle {
  square_t squares[NUM_ROWS][NUM_COLS];
} puzzle_t;

void solve(unsigned char grid[9][9]);

// following are static ("private") function declarations --- add as needed

static puzzle_t *create_puzzle(unsigned char grid[9][9]);
static void init_peers(puzzle_t *puz, int row, int col);
static puzzle_t *copy_puzzle(puzzle_t *puz);
static void free_puzzle(puzzle_t *puz);
static void print_puzzle(puzzle_t *);

static puzzle_t *search(puzzle_t *puz);
static puzzle_t *assign(puzzle_t *puz, int row, int col, char val);
static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val);

static void set_init_vals(puzzle_t *puz, int row, int col, char val);

/*************************/
/* Public solve function */
/*************************/

void solve(unsigned char grid[9][9]) {
  puzzle_t *puz = create_puzzle(grid);
  puzzle_t *solved;
  if ((solved = search(puz)) != NULL) {
    print_puzzle(solved);
  }
  free_puzzle(puz);
}

/*******************************************/
/* Puzzle data structure related functions */
/*******************************************/

static puzzle_t *create_puzzle(unsigned char vals[9][9]) {
  puzzle_t *puz = malloc(sizeof(puzzle_t));
  int x, y;
  for (x = 0; x < NUM_DIGITS; x++) {
    for (y = 0; y < NUM_DIGITS; y++) {
      set_init_vals(puz, x, y, vals[x][y]);
      puz->squares[x][y].row = y;
      puz->squares[x][y].col = x;
    }
  }
  return puz;
}

static void init_peers(puzzle_t *puz, int row, int col) {
}

static void free_puzzle(puzzle_t *puz) {
}

static puzzle_t *copy_puzzle(puzzle_t *puz) {
  return NULL;
}

void print_puzzle(puzzle_t *p) {
  int i, j;
  for (i=0; i<NUM_ROWS; i++) {
    for (j=0; j<NUM_COLS; j++) {
      printf(" %9s", p->squares[i][j].vals); // may be useful while debugging
      //printf(" %2s", p->squares[i][j].vals);
    }
    printf("\n");
  }
}

/**********/
/* Search */
/**********/

static puzzle_t *search(puzzle_t *puz) {
  // short circuit to print puzzle
  return puz;
}

/**************************/
/* Constraint propagation */
/**************************/

static puzzle_t *assign(puzzle_t *puz, int row, int col, char val) {
  return NULL;
}

static puzzle_t *eliminate(puzzle_t *puz, int row, int col, char val) {
  return NULL;
}

/*****************************************/
/* Misc (e.g., utility) functions follow */
/*****************************************/
static void set_init_vals(puzzle_t *puz, int row, int col, char val) {
  if (val >= '1' && val <= '9') {
    // assign vals as the digit
    puz->squares[row][col].vals[0] = val;
    puz->squares[row][col].vals[1] = '\0';
  }
  else {
    // copy list of digits in to vals
    strncpy(puz->squares[row][col].vals, DIGITS, NUM_DIGITS + 1);
  }
}
