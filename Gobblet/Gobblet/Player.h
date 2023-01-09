#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:

	Player();
	~Player();

	void update(sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);



	sf::CircleShape m_largePiece;
	sf::CircleShape m_mediumPiece;
	sf::CircleShape m_smallPiece;
	sf::CircleShape m_tinyPiece;

	bool m_playerTurn = true;
	sf::Vector2f m_mouseLocation;
	sf::CircleShape m_mousePositionShape;
};

