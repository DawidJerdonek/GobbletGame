#pragma once
#include <SFML/Graphics.hpp>
class NPC
{
public:

	NPC();
	~NPC();

	void update();
	void render(sf::RenderWindow& t_window);



	sf::CircleShape largePiece;
	sf::CircleShape mediumPiece;
	sf::CircleShape smallPiece;
	sf::CircleShape tinyPiece;
};

