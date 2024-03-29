#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// The NPC's pieces and other required variables
/// </summary>
class NPC
{
public:

	NPC();
	~NPC();

	void update();
	void render(sf::RenderWindow& t_window);

	// Create one set of pieces
	sf::CircleShape m_largePiece;
	sf::CircleShape m_mediumPiece;
	sf::CircleShape m_smallPiece;
	sf::CircleShape m_tinyPiece;

	//Check if each piece is currently in play
	bool largePieceInPlay = false;
	bool mediumPieceInPlay = false;
	bool smallPieceInPlay = false;
	bool tinyPieceInPlay = false;

	//Set initial position of pieces
	int largePieceYCoords = 200;
	int mediumPieceYCoords = 400;
	int smallPieceYCoords = 600;
	int tinyPieceYCoords = 800;

	sf::Vector2f largePieceBoardCoords{ -1,-1 };
	sf::Vector2f mediumPieceBoardCoords{ -1,-1 };
	sf::Vector2f smallPieceBoardCoords{ -1,-1 };
	sf::Vector2f tinyPieceBoardCoords{ -1,-1 };
};