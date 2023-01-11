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

	sf::Text idText;
	sf::Vector2f center;

	bool IsOccupiedByPlayer = false;
	bool IsOccupiedByNPC = false;

	bool m_isMarked{ false };
	int m_parentCellId;

	int getID() const;
	
	int pieceIndex = -1;

	std::vector<std::pair<int, int>> piecesOrder;
};