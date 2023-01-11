#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:

	Player();
	~Player();

	void update(sf::RenderWindow& t_window, bool& t_playersTurn);
	void render(sf::RenderWindow& t_window);



	sf::CircleShape m_largePiece;
	sf::CircleShape m_mediumPiece;
	sf::CircleShape m_smallPiece;
	sf::CircleShape m_tinyPiece;

	sf::Vector2f m_mouseLocation;

	sf::Vector2f m_startPosition;
	bool m_tinyPieceSnapped = false;
	bool m_smallPieceSnapped = false;
	bool m_mediumPieceSnapped = false;
	bool m_largePieceSnapped = false;
	sf::Vector2f m_tinyPiecePreviousPos;
	sf::Vector2f m_smallPiecePreviousPos;
	sf::Vector2f m_mediumPiecePreviousPos;
	sf::Vector2f m_largePiecePreviousPos;
};