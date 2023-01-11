#pragma once
#include <SFML/Graphics.hpp>
/// <summary>
/// The Players vars and gameplay/board pieces
/// </summary>
class Player
{
public:

	Player();
	~Player();

	void update(sf::RenderWindow& t_window, bool& t_playersTurn);
	void render(sf::RenderWindow& t_window);

	// Get position of mouse on screen
	sf::Vector2f m_mouseLocation;

	//Start position stored to reset pieces into position beside board
	sf::Vector2f m_startPosition;

	// Create one set of pieces
	sf::CircleShape m_largePiece;
	sf::CircleShape m_mediumPiece;
	sf::CircleShape m_smallPiece;
	sf::CircleShape m_tinyPiece;

	//Check is a piece is snapped onto the board
	bool m_tinyPieceSnapped = false;
	bool m_smallPieceSnapped = false;
	bool m_mediumPieceSnapped = false;
	bool m_largePieceSnapped = false;

	// Store previous positions of pieces
	sf::Vector2f m_tinyPiecePreviousPos;
	sf::Vector2f m_smallPiecePreviousPos;
	sf::Vector2f m_mediumPiecePreviousPos;
	sf::Vector2f m_largePiecePreviousPos;
};