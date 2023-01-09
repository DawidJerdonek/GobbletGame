#include "NPC.h"
#include <iostream>

NPC::NPC()
{
	largePiece.setFillColor(sf::Color::Black);
	largePiece.setRadius(100);
	largePiece.setOutlineThickness(2);
	largePiece.setOutlineColor(sf::Color::White);
	largePiece.setOrigin(largePiece.getGlobalBounds().width / 2, largePiece.getGlobalBounds().height / 2);
	largePiece.setPosition(1450, largePieceYCoords);

	mediumPiece.setFillColor(sf::Color::Black);
	mediumPiece.setRadius(80);
	mediumPiece.setOutlineThickness(2);
	mediumPiece.setOutlineColor(sf::Color::White);
	mediumPiece.setOrigin(mediumPiece.getGlobalBounds().width / 2, mediumPiece.getGlobalBounds().height / 2);
	mediumPiece.setPosition(1450, mediumPieceYCoords);

	smallPiece.setFillColor(sf::Color::Black);
	smallPiece.setRadius(60);
	smallPiece.setOutlineThickness(2);
	smallPiece.setOutlineColor(sf::Color::White);
	smallPiece.setOrigin(smallPiece.getGlobalBounds().width / 2, smallPiece.getGlobalBounds().height / 2);
	smallPiece.setPosition(1450, smallPieceYCoords);

	tinyPiece.setFillColor(sf::Color::Black);
	tinyPiece.setRadius(40);
	tinyPiece.setOutlineThickness(2);
	tinyPiece.setOutlineColor(sf::Color::White);
	tinyPiece.setOrigin(tinyPiece.getGlobalBounds().width / 2, tinyPiece.getGlobalBounds().height / 2);
	tinyPiece.setPosition(1450, tinyPieceYCoords);
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
	t_window.draw(largePiece);
	t_window.draw(mediumPiece);
	t_window.draw(smallPiece);
	t_window.draw(tinyPiece);
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