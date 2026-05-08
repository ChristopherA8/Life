#include <iostream>
#include "defs.h"

int inline randomNumber(int min, int max) {
   return min + (rand() % (max + 1));
}

auto c = [](int col, int row) { return row * (WINDOW_WIDTH / CELL_SIZE) + col; };
