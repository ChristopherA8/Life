#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "defs.h"

class Game {
   private:
   sf::RenderWindow& _window;
   std::vector<int> _cells;
   void _drawCell(int col, int row, int cellSize, sf::Color color = sf::Color::White);
   int _countLivingNeighbors(int index);
   // sf::Font font;

   public:
   Game(sf::RenderWindow& window);

   void initCells();
   void toggleCell(int index);
   void update();
   void draw();
};