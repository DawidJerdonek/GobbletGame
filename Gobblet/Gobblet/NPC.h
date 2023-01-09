#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Cell.h"

class NPC
{
public:

	NPC();
	~NPC();

	void update(bool& t_playersTurn);
	void render(sf::RenderWindow& t_window);

	void minimax(int depth, Grid& t_grid, bool& t_playersTurn);
	Cell& findBestMove(Grid& t_grid);
	void movePlayer(sf::Vector2f& currentPos, Grid& t_grid);
	void unMovePlayer(sf::Vector2f& currentPos, Grid& t_grid);

	sf::CircleShape largePiece;
	sf::CircleShape mediumPiece;
	sf::CircleShape smallPiece;
	sf::CircleShape tinyPiece;

	bool largePieceInPlay = false;
	bool mediumPieceInPlay = false;
	bool smallPieceInPlay = false;
	bool tinyPieceInPlay = false;

	int largePieceYCoords = 200;
	int mediumPieceYCoords = 400;
	int smallPieceYCoords = 600;
	int tinyPieceYCoords = 800;
};