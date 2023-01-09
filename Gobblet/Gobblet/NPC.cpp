#include "NPC.h"
#include <iostream>

NPC::NPC()
{
	m_largePiece.setFillColor(sf::Color::Black);
	m_largePiece.setRadius(100);
	m_largePiece.setOutlineThickness(2);
	m_largePiece.setOutlineColor(sf::Color::White);
	m_largePiece.setOrigin(m_largePiece.getGlobalBounds().width / 2, m_largePiece.getGlobalBounds().height / 2);
	m_largePiece.setPosition(1450, largePieceYCoords);

	m_mediumPiece.setFillColor(sf::Color::Black);
	m_mediumPiece.setRadius(80);
	m_mediumPiece.setOutlineThickness(2);
	m_mediumPiece.setOutlineColor(sf::Color::White);
	m_mediumPiece.setOrigin(m_mediumPiece.getGlobalBounds().width / 2, m_mediumPiece.getGlobalBounds().height / 2);
	m_mediumPiece.setPosition(1450, mediumPieceYCoords);

	m_smallPiece.setFillColor(sf::Color::Black);
	m_smallPiece.setRadius(60);
	m_smallPiece.setOutlineThickness(2);
	m_smallPiece.setOutlineColor(sf::Color::White);
	m_smallPiece.setOrigin(m_smallPiece.getGlobalBounds().width / 2, m_smallPiece.getGlobalBounds().height / 2);
	m_smallPiece.setPosition(1450, smallPieceYCoords);

	m_tinyPiece.setFillColor(sf::Color::Black);
	m_tinyPiece.setRadius(40);
	m_tinyPiece.setOutlineThickness(2);
	m_tinyPiece.setOutlineColor(sf::Color::White);
	m_tinyPiece.setOrigin(m_tinyPiece.getGlobalBounds().width / 2, m_tinyPiece.getGlobalBounds().height / 2);
	m_tinyPiece.setPosition(1450, tinyPieceYCoords);
}

NPC::~NPC()
{
}

void NPC::update(bool& t_playersTurn)
{
	if (!t_playersTurn) 
	{
		// run minimax alg
	}
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tinyPiece);
	t_window.draw(m_smallPiece);
	t_window.draw(m_mediumPiece);
	t_window.draw(m_largePiece);
}

void NPC::minimax(int depth, Grid& t_grid, bool& t_playersTurn)
{
	if (!t_playersTurn)
	{
		int best = -1000;

		for (int y = 0; y < t_grid.YAmountCells; y++)
		{
			for (int x = 0; x < t_grid.XAmountCells; x++)
			{
				if (!t_grid.cellGrid[x][y].IsOccupiedByPlayer || !t_grid.cellGrid[x][y].IsOccupiedByNPC)
				{
					//do stuff here for minimax alg
				}
			}
		}
	}
}

Cell& NPC::findBestMove(Grid& t_grid)
{
	int bestVal = -1000;
	Cell& bestMove = t_grid.cellGrid[0][0];


	for (int y = 0; y < t_grid.YAmountCells; y++)
	{
		for (int x = 0; x < t_grid.XAmountCells; x++)
		{
			//do more stuff here to find best move
		}
	}

	return bestMove;
}

void NPC::movePlayer(sf::Vector2f& currentPos, Grid& t_grid)
{
	//move the player
}

void NPC::unMovePlayer(sf::Vector2f& currentPos, Grid& t_grid)
{
	//unmove the player
}