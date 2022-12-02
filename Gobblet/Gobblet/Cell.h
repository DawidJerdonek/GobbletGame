#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell();

	sf::RectangleShape cellBody;
	int m_id{ -1 };
	int x;
	int y;

	int m_previousCellId{ -1 };

	sf::Text idText;
	sf::Vector2f center;

	bool m_isMarked{ false };
	int m_parentCellId;

	int getID() const;
};