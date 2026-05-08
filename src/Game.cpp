#include "Game.h"
#include "util.h"

Game::Game(sf::RenderWindow& window) : _window(window), 
                                       playPauseTexture(_loadTexture("./assets/playpause_black.png")),
                                       bugTexture(_loadTexture("./assets/bug.png")),
                                       minusTexture(_loadTexture("./assets/minus.png")),
                                       plusTexture(_loadTexture("./assets/plus.png")),
                                       playPauseSprite(playPauseTexture),
                                       bugSprite(bugTexture),
                                       minusSprite(minusTexture),
                                       plusSprite(plusTexture) {
   this->_font.openFromFile("./assets/Charter.ttc");
   this->_generation = 1;
   this->_debugPanelHidden = true;
}

sf::Texture Game::_loadTexture(const std::string& path) {
    sf::Texture t;
    t.loadFromFile(path);
    return t;
}

void Game::_drawGrid() {
   sf::VertexArray grid(sf::PrimitiveType::Lines);
   const sf::Color grayColor = sf::Color(120, 120, 120);

   // Vertical lines
   for (int x = 0; x <= WINDOW_WIDTH; x += CELL_SIZE) {
      grid.append(sf::Vertex{sf::Vector2f(x, 0), grayColor});
      grid.append(sf::Vertex{sf::Vector2f(x, WINDOW_HEIGHT), grayColor});
   }

   // Horizontal lines
   for (int y = 0; y <= WINDOW_HEIGHT; y += CELL_SIZE) {
      grid.append(sf::Vertex{sf::Vector2f(0, y), grayColor});
      grid.append(sf::Vertex{sf::Vector2f(WINDOW_WIDTH, y), grayColor});
   }

   this->_window.draw(grid);
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

   int horizontalCellCount = WINDOW_WIDTH / CELL_SIZE;
   int verticalCellCount = WINDOW_HEIGHT / CELL_SIZE;
   int totalCells = horizontalCellCount * verticalCellCount;

   for (size_t i = 0; i < totalCells; i++) {
      // this->_cells.push_back((randomNumber(0, 100) < 25));
      this->_cells.push_back(0);
   }

   // // Glider Example
   // this->toggleCell(340);
   // this->toggleCell(341);
   // this->toggleCell(341 - 80);
   // this->toggleCell(342);
   // this->toggleCell(342 - 40);

   // // Pulsar Oscillator
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


   // this->toggleCell((c(30, 20)));
   // this->toggleCell((c(31, 20)));
   // this->toggleCell((c(32, 20)));
   // this->toggleCell((c(32, 19)));
   // this->toggleCell((c(33, 19)));
   // this->toggleCell((c(34, 19)));
}

void Game::_drawControls() {
   auto [pWidth, pHeight] = this->playPauseTexture.getSize();
   auto [bWidth, bHeight] = this->bugTexture.getSize();
   auto [mWidth, mHeight] = this->minusTexture.getSize();
   auto [plWidth, plHeight] = this->plusTexture.getSize();

   playPauseSprite.setPosition({float(WINDOW_WIDTH - pWidth) - 15, float(pHeight) - 20});
   playPauseSprite.setColor(sf::Color::White);
   playPauseSprite.setScale({1.5, 1.5});
   this->_window.draw(playPauseSprite);

   bugSprite.setPosition({float(WINDOW_WIDTH - (bWidth * 2)) - (28), float(bHeight) - 20});
   bugSprite.setColor(sf::Color::White);
   bugSprite.setScale({1.5, 1.5});
   this->_window.draw(bugSprite);

   plusSprite.setPosition({float(WINDOW_WIDTH - (bWidth * 3)) - (45), float(bHeight) - 20});
   plusSprite.setColor(sf::Color::White);
   plusSprite.setScale({1.5, 1.5});
   this->_window.draw(plusSprite);

   minusSprite.setPosition({float(WINDOW_WIDTH - (bWidth * 4)) - (60), float(bHeight) - 20});
   minusSprite.setColor(sf::Color::White);
   minusSprite.setScale({1.5, 1.5});
   this->_window.draw(minusSprite);
}

void Game::_drawInfoPanel() {
   int alive = std::count(this->_cells.begin(), this->_cells.end(), 1);
   std::string info = "Generation: ";
   info += std::to_string(this->_generation);
   info += "\nPopulation: ";
   info += std::to_string(alive);

   sf::Text text(this->_font, info, 18);
   text.setFillColor(sf::Color::White);
   text.setPosition(sf::Vector2f(10.f, 10.f));

   this->_window.draw(text);
}

void Game::_drawDebugPanel() {
   std::string info = "Living cells:\n";

   for (int i = 0; i < this->_cells.size(); i++) {
      if (this->_cells[i] == 1) {
         int col = i % (WINDOW_WIDTH / CELL_SIZE);
         int row = i / (WINDOW_WIDTH / CELL_SIZE);
         info += "(" + std::to_string(col) + ", " + std::to_string(row) + ")\n";
      }
   }

   sf::Text text(this->_font, info, 18);
   text.setFillColor(sf::Color::White);
   text.setPosition(sf::Vector2f(10.f, 60.f));

   this->_window.draw(text);
}

void Game::toggleCell(int index) {
   this->_cells[index] = this->_cells[index] ? 0 : 1;
}

void Game::toggleDebugPanel() {
   this->_debugPanelHidden = this->_debugPanelHidden ? false : true;
   this->_window.clear(sf::Color(0, 0, 0));
   this->draw();
   this->_window.display();
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
   this->_generation++;
   this->_window.clear(sf::Color(0, 0, 0));
}

int Game::_countLivingNeighbors(int index) {
   int x = index % (WINDOW_WIDTH / CELL_SIZE);
   int y = index / (WINDOW_WIDTH / CELL_SIZE);
   int livingNeighborCount = 0;

   for (size_t i = 0; i < this->_cells.size(); i++) {
      int n_x = i % (WINDOW_WIDTH / CELL_SIZE);
      int n_y = i / (WINDOW_WIDTH / CELL_SIZE);
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
      }
   }

   return livingNeighborCount;
}

void Game::clearCells() {
   this->_cells.clear();
}

void Game::draw() {
   this->_drawGrid();
   this->_drawControls();
   this->_drawInfoPanel();
   if (!this->_debugPanelHidden) this->_drawDebugPanel();

   for (size_t i = 0; i < this->_cells.size(); i++) {
      if (this->_cells[i]) {
         this->_drawCell(i % (WINDOW_WIDTH / CELL_SIZE), i / (WINDOW_WIDTH / CELL_SIZE), CELL_SIZE);
      }
   }
}

void Game::_drawCell(int col, int row, int cellSize, sf::Color color) {
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1)); // -1 leaves grid line visible
    cell.setPosition(sf::Vector2f(col * cellSize + 1, row * cellSize + 1));
    cell.setFillColor(color);
    this->_window.draw(cell);
}