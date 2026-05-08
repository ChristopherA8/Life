#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "defs.h"

class Game {
   private:
   sf::RenderWindow& _window;
   std::vector<int> _cells;
   int _generation;
   void _drawGrid();
   void _drawCell(int col, int row, int cellSize, sf::Color color = sf::Color::White);
   void _drawControls();
   void _drawInfoPanel();
   void _drawDebugPanel();
   bool _debugPanelHidden;
   int _countLivingNeighbors(int index);
   sf::Font _font;
   static sf::Texture _loadTexture(const std::string& path);

   public:
   Game(sf::RenderWindow& window);

   sf::Texture playPauseTexture;
   sf::Texture bugTexture;
   sf::Texture minusTexture;
   sf::Texture plusTexture;
   sf::Sprite playPauseSprite;
   sf::Sprite bugSprite;
   sf::Sprite minusSprite;
   sf::Sprite plusSprite;

   void initCells();
   void clearCells();
   void toggleCell(int index);
   void toggleDebugPanel();
   void update();
   void draw();
};