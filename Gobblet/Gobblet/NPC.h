#pragma once
#include <SFML/Graphics.hpp>


class NPC
{
public:

	NPC();
	~NPC();

	void update();
	void render(sf::RenderWindow& t_window);

	sf::CircleShape m_largePiece;
	sf::CircleShape m_mediumPiece;
	sf::CircleShape m_smallPiece;
	sf::CircleShape m_tinyPiece;

	bool largePieceInPlay = false;
	bool mediumPieceInPlay = false;
	bool smallPieceInPlay = false;
	bool tinyPieceInPlay = false;

	int largePieceYCoords = 200;
	int mediumPieceYCoords = 400;
	int smallPieceYCoords = 600;
	int tinyPieceYCoords = 800;

	sf::Vector2f largePieceBoardCoords{ -1,-1 };
	sf::Vector2f mediumPieceBoardCoords{ -1,-1 };
	sf::Vector2f smallPieceBoardCoords{ -1,-1 };
	sf::Vector2f tinyPieceBoardCoords{ -1,-1 };
};