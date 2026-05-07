#pragma once

#include <SFML/Graphics.hpp>

const sf::Color grayColor = sf::Color(120, 120, 120);

sf::VertexArray createGrid(int windowWidth, int windowHeight, int cellSize);
