#include "Game.h"
#include "util.h"

Game::Game(sf::RenderWindow& window) : _window(window) {
   // this->font.openFromFile("/System/Library/Fonts/Supplemental/Charter.ttc");
}

void Game::initCells() {
   /*
      Instructions:
      In the initial cell configuration, 
      there is a 25% chance that there 
      will be a living organism in the cell.

      My parameters:
      #define WINDOW_HEIGHT 800
      #define WINDOW_WIDTH 600
      #define CELL_SIZE 20

      Horizontal cells: 600 / 20 = 30 cells wide
      Vertical cells: 800 / 20 = 40 cells tall
      30 × 40 = 1,200 total cells
   */

   for (size_t i = 0; i < 1200; i++) {
      this->_cells.push_back((randomNumber(0, 100) < 25));
      // this->_cells.push_back(0);
   }

   // Glider Example
   // this->toggleCell(340);
   // this->toggleCell(341);
   // this->toggleCell(341 - 80);
   // this->toggleCell(342);
   // this->toggleCell(342 - 40);

   // Pulsar Oscillator
   // // Top outer rows
   // this->toggleCell(c(9,  7)); this->toggleCell(c(10, 7)); this->toggleCell(c(11, 7));
   // this->toggleCell(c(15, 7)); this->toggleCell(c(16, 7)); this->toggleCell(c(17, 7));

   // // Upper middle rows
   // this->toggleCell(c(7,  9)); this->toggleCell(c(12, 9)); this->toggleCell(c(14, 9)); this->toggleCell(c(19, 9));
   // this->toggleCell(c(7,  10)); this->toggleCell(c(12, 10)); this->toggleCell(c(14, 10)); this->toggleCell(c(19, 10));
   // this->toggleCell(c(7,  11)); this->toggleCell(c(12, 11)); this->toggleCell(c(14, 11)); this->toggleCell(c(19, 11));

   // // Middle outer rows
   // this->toggleCell(c(9,  12)); this->toggleCell(c(10, 12)); this->toggleCell(c(11, 12));
   // this->toggleCell(c(15, 12)); this->toggleCell(c(16, 12)); this->toggleCell(c(17, 12));

   // this->toggleCell(c(9,  14)); this->toggleCell(c(10, 14)); this->toggleCell(c(11, 14));
   // this->toggleCell(c(15, 14)); this->toggleCell(c(16, 14)); this->toggleCell(c(17, 14));

   // // Lower middle rows
   // this->toggleCell(c(7,  15)); this->toggleCell(c(12, 15)); this->toggleCell(c(14, 15)); this->toggleCell(c(19, 15));
   // this->toggleCell(c(7,  16)); this->toggleCell(c(12, 16)); this->toggleCell(c(14, 16)); this->toggleCell(c(19, 16));
   // this->toggleCell(c(7,  17)); this->toggleCell(c(12, 17)); this->toggleCell(c(14, 17)); this->toggleCell(c(19, 17));

   // // Bottom outer rows
   // this->toggleCell(c(9,  19)); this->toggleCell(c(10, 19)); this->toggleCell(c(11, 19));
   // this->toggleCell(c(15, 19)); this->toggleCell(c(16, 19)); this->toggleCell(c(17, 19));
}

void Game::toggleCell(int index) {
   this->_cells[index] = this->_cells[index] ? 0 : 1;
}

/*
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void Game::update() {
   // Copy current state before mutating
   std::vector<int> next = this->_cells;

   for (size_t i = 0; i < this->_cells.size(); i++) {
      int neighbors = this->_countLivingNeighbors(i);

      if (this->_cells[i]) {
         // Cell is living
         if (neighbors < 2 || neighbors > 3) next[i] = 0;
      } else {
         // Cell is dead
         if (neighbors == 3) next[i] = 1;
      }
   }

   this->_cells = next;
}

int Game::_countLivingNeighbors(int index) {
   int x = index % 40;
   int y = index / 40;
   int livingNeighborCount = 0;

   for (size_t i = 0; i < this->_cells.size(); i++) {
      int n_x = i % 40;
      int n_y = i / 40;
      if ((n_x == x     && n_y == y - 1) || // top
          (n_x == x     && n_y == y + 1) || // bottom
          (n_x == x - 1 && n_y == y    ) || // left
          (n_x == x + 1 && n_y == y    ) || // right
          (n_x == x - 1 && n_y == y - 1) || // top left
          (n_x == x + 1 && n_y == y - 1) || // top right
          (n_x == x - 1 && n_y == y + 1) || // bottom left
          (n_x == x + 1 && n_y == y + 1)) { // bottom right
         if (this->_cells[i]) {
            livingNeighborCount++;
         }
         // Test neighbor logic
         // this->_drawCell(n_x, n_y, CELL_SIZE, sf::Color::Green);
      }
   }

   return livingNeighborCount;
}

void Game::draw() {
   for (size_t i = 0; i < this->_cells.size(); i++) {
      if (this->_cells[i]) {
         this->_drawCell(i % 40, i / 40, CELL_SIZE);
         // Test neighbor logic
         // this->_countLivingNeighbors(i);
      }
   }

   // // Debug Panel
   // std::string info = "Living cells:\n";

   // for (int i = 0; i < this->_cells.size(); i++) {
   //    if (this->_cells[i] == 1) {
   //       int col = i % 40;
   //       int row = i / 40;
   //       info += "(" + std::to_string(col) + ", " + std::to_string(row) + ")\n";
   //    }
   // }

   // sf::Text text(font, info, 14);
   // text.setFillColor(sf::Color::White);
   // text.setPosition(sf::Vector2f(10.f, 10.f));

   // this->_window.draw(text);
}

void Game::_drawCell(int col, int row, int cellSize, sf::Color color) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1)); // -1 leaves grid line visible
    cell.setPosition(sf::Vector2f(col * cellSize + 1, row * cellSize + 1));
    cell.setFillColor(color);
    this->_window.draw(cell);
}