#include <iostream>

#include "main.h"
#include "Game.h"
#include "util.h"
#include "defs.h"

int main() {
   srand(time(0));

   sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game of Life", (sf::Style::Close | sf::Style::Titlebar));
   Game game = Game(window);

   sf::Clock clock = sf::Clock();
   const sf::Time update_interval = sf::seconds(2.0f);
   // const sf::Time update_interval = sf::seconds(0.2f);

   // Grid array
   sf::VertexArray grid = createGrid(WINDOW_WIDTH, WINDOW_HEIGHT, 20);
   
   // Initial Setup
   window.clear(sf::Color(0, 0, 0));
   window.draw(grid);
   game.initCells();
   game.draw();
   window.display();

   while (window.isOpen()) {
      while (const std::optional event = window.pollEvent()) {
         if (event->is<sf::Event::Closed>()) window.close();
      }

      if (clock.getElapsedTime() >= update_interval) {
         clock.restart();

         game.update();
         window.clear(sf::Color(0, 0, 0));
         window.draw(grid);

         game.draw();
         window.display();
      }
   }
}

sf::VertexArray createGrid(int windowWidth, int windowHeight, int cellSize) {
   sf::VertexArray grid(sf::PrimitiveType::Lines);

   // Vertical lines
   for (int x = 0; x <= windowWidth; x += cellSize) {
      grid.append(sf::Vertex{sf::Vector2f(x, 0), grayColor});
      grid.append(sf::Vertex{sf::Vector2f(x, windowHeight), grayColor});
   }

   // Horizontal lines
   for (int y = 0; y <= windowHeight; y += cellSize) {
      grid.append(sf::Vertex{sf::Vector2f(0, y), grayColor});
      grid.append(sf::Vertex{sf::Vector2f(windowWidth, y), grayColor});
   }

   return grid;
}