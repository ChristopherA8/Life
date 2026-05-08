#include <iostream>

#include "main.h"
#include "Game.h"
#include "util.h"
#include "defs.h"

int CELL_SIZE = 20;

int main() {
   srand(time(0));

   sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Game of Life", (sf::Style::Close | sf::Style::Titlebar));
   Game game = Game(window);

   bool isRunning = 1;
   sf::Clock clock = sf::Clock();
   // const sf::Time update_interval = sf::seconds(2.0f);
   const sf::Time update_interval = sf::seconds(0.1f);
   
   // Initial Setup
   window.clear(sf::Color(0, 0, 0));
   game.initCells();
   game.draw();
   window.display();

   while (window.isOpen()) {
      while (const std::optional event = window.pollEvent()) {
         if (event->is<sf::Event::Closed>()) window.close();
         if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (game.playPauseSprite.getGlobalBounds().contains({ float(mouseEvent->position.x), float(mouseEvent->position.y) })) {
               isRunning = isRunning ? false : true;
               clock.restart();
               continue;
            }

            if (game.bugSprite.getGlobalBounds().contains({ float(mouseEvent->position.x), float(mouseEvent->position.y) })) {
               game.toggleDebugPanel();
               continue;
            }

            if (game.plusSprite.getGlobalBounds().contains({ float(mouseEvent->position.x), float(mouseEvent->position.y) })) {
               CELL_SIZE += 5;
               window.clear(sf::Color(0, 0, 0));
               game.clearCells();
               game.initCells();
               game.draw();
               window.display();
               continue;
            }

            if (game.minusSprite.getGlobalBounds().contains({ float(mouseEvent->position.x), float(mouseEvent->position.y) })) {
               CELL_SIZE -= 5;
               window.clear(sf::Color(0, 0, 0));
               game.clearCells();
               game.initCells();
               game.draw();
               window.display();
               continue;
            }

            int col = mouseEvent->position.x / CELL_SIZE;
            int row = mouseEvent->position.y / CELL_SIZE;
            game.toggleCell(c(col, row));
            window.clear(sf::Color(0, 0, 0));
            game.draw();
            window.display();
         }
      }

      if (clock.getElapsedTime() >= update_interval) {
         if (!isRunning) continue;
         clock.restart();

         game.update();

         game.draw();
         window.display();
      }
   }
}