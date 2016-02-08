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
static int assign(puzzle_t *puz, int row, int col, char val);
static int eliminate(puzzle_t *puz, int row, int col, char val);

static void set_init_vals(puzzle_t *puz, int row, int col, char val);
static void remove_char(char *str, const char rem);

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
      init_peers(puz, x, y);
    }
  }
  return puz;
}

static void init_peers(puzzle_t *puz, int row, int col) {
  // p is current peer index
  int x,y,p = 0;
  // first unit
  for (x = 0; x < NUM_COLS; x++) {
    puz->squares[row][col].units[0][x] = &puz->squares[row][x];
    if (x != col) {
      puz->squares[row][col].peers[p++] = &puz->squares[row][x];
    }
  }

  // second unit
  for (y = 0; y < NUM_ROWS; y++) {
    puz->squares[row][col].units[1][y] = &puz->squares[y][col];
    if (y != row) {
      puz->squares[row][col].peers[p++] = &puz->squares[y][col];
    }
  }

  // third unit
  int top  = row - (row % 3);
  int left = col - (col % 3);
  int k = 0;
  for (x = top; x < NUM_UNITS + top; x++) {
    for (y = left; y < NUM_UNITS + left; y++) {
      puz->squares[row][col].units[2][k++] = &puz->squares[x][y];
      if ((x != row) && (y != col)) {
        puz->squares[row][col].peers[p++] = &puz->squares[x][y];
      }
    }
  }
}

static void free_puzzle(puzzle_t *puz) {
  free(puz);
}

static puzzle_t *copy_puzzle(puzzle_t *puz) {
  puzzle_t *new_puz = malloc(sizeof(puzzle_t));
  memcpy(new_puz, puz, sizeof(puzzle_t));
  // then re-initialize peers
  int x,y;
  for (x=0; x < NUM_COLS; x++) {
    for (y = 0; y < NUM_ROWS; y++) {
      init_peers(new_puz, x, y);
    }
  }
  return new_puz;
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
  int row, col;
  char *vals;
  for (row = 0; row < NUM_ROWS; row++) {
    for (col = 0; col < NUM_COLS; col++) {
      vals = puz->squares[row][col].vals;
      //if (strlen(vals) == 1)
      puzzle_t *new_puz = copy_puzzle(puz);
      if (assign(new_puz, row, col, vals[0])) {
        free_puzzle(puz);
        puz = new_puz;
      }
      else {
        free_puzzle(new_puz);
      }
    }
  }
  return puz;
}

/**************************/
/* Constraint propagation */
/**************************/

static int assign(puzzle_t *puz, int row, int col, char val) {
  int i, r = 1;
  char *vals = puz->squares[row][col].vals;
  for (i = 0; i < strlen(vals); i++) {
    if (vals[i] != val)
      r &= eliminate(puz, row, col, vals[i]);
  }
  return r;
}

static int eliminate(puzzle_t *puz, int row, int col, char val) {
  char *vals = puz->squares[row][col].vals;

  // if val is already eliminated
  if (strchr(vals, val) == NULL)
    return 1;

  remove_char(vals, val);

  // (1) If a square is reduced to one value, then eliminate
  //     it from the peers
  //
  if (strlen(vals) == 0) // contradiction
    return 0;
  else if (strlen(vals) == 1) {
    char *val2;
    int i, c_row, c_col, r;
    strcpy(val2, vals);
    for (i = 0; i < NUM_PEERS; i++) {
      c_row = puz->squares[row][col].peers[i]->row;
      c_col = puz->squares[row][col].peers[i]->col;
      if (!eliminate(puz, c_row, c_col, val2[0]))
        return 0;
    }
  }

  // (2) If a unit is reduced to only one place for a value,
  //     then put it there
  //
  int u, d, d_places = 0;
  for (u = 0; u < NUM_UNITS; u++) {
    for (d = 0; d < NUM_DIGITS; d++) {
      if (strchr(puz->squares[row][col].units[u][d]->vals, val)) {
        d_places ++;
      }
      if (d_places) ;
      // [TODO: Create proper implementation of this]
    }
  }
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
  puz->squares[row][col].row = row;
  puz->squares[row][col].col = col;
}

static void remove_char(char *str, const char rem) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != rem) dst++;
    }
    *dst = '\0';
}
