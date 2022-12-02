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
	static const int xAmountCells = 4;
	static const int YAmountCells = 4;
	static const int TotalCells = 16;

	Cell* at(int t_index);
	Grid();
	~Grid();
	void setupGrid();
	void draw(sf::RenderWindow& m_window);
	void reset();
	void update();

	sf::Font idFont;
	Cell cellGrid[xAmountCells][YAmountCells];

	Cell* GetIntersects(sf::Vector2f pos);
};
