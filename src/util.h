#include <iostream>

int inline randomNumber(int min, int max) {
   return min + (rand() % (max + 1));
}

auto c = [](int col, int row) { return row * 40 + col; };
