#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include "Cell.h"
#include "GLOBALS.h"

class Grid
{
public:
	static const int XAmountCells = 4;
	static const int YAmountCells = 4;
	static const int TotalCells = 16;

	sf::Vector2f offset{ 350, 0 };

	Cell* at(int t_index);
	Grid();
	~Grid();
	void setupGrid();
	void draw(sf::RenderWindow& m_window);
	void reset();
	void update(sf::RenderWindow& t_window);
	sf::Color defaultColor{ 150, 78, 0, 255 };
	sf::Color highlightedColor{ 170, 98, 20, 255 };


	sf::Font idFont;
	Cell cellGrid[XAmountCells][YAmountCells];

	Cell* GetIntersects(sf::Vector2f pos);
};
