#include "NPC.h"
#include <iostream>

NPC::NPC()
{
	largePiece.setFillColor(sf::Color::Black);
	largePiece.setRadius(100);
	largePiece.setOutlineThickness(2);
	largePiece.setOutlineColor(sf::Color::White);
	largePiece.setOrigin(largePiece.getGlobalBounds().width / 2, largePiece.getGlobalBounds().height / 2);
	largePiece.setPosition(1450, 200);

	mediumPiece.setFillColor(sf::Color::Black);
	mediumPiece.setRadius(80);
	mediumPiece.setOutlineThickness(2);
	mediumPiece.setOutlineColor(sf::Color::White);
	mediumPiece.setOrigin(mediumPiece.getGlobalBounds().width / 2, mediumPiece.getGlobalBounds().height / 2);
	mediumPiece.setPosition(1450, 400);

	smallPiece.setFillColor(sf::Color::Black);
	smallPiece.setRadius(60);
	smallPiece.setOutlineThickness(2);
	smallPiece.setOutlineColor(sf::Color::White);
	smallPiece.setOrigin(smallPiece.getGlobalBounds().width / 2, smallPiece.getGlobalBounds().height / 2);
	smallPiece.setPosition(1450, 600);

	tinyPiece.setFillColor(sf::Color::Black);
	tinyPiece.setRadius(40);
	tinyPiece.setOutlineThickness(2);
	tinyPiece.setOutlineColor(sf::Color::White);
	tinyPiece.setOrigin(tinyPiece.getGlobalBounds().width / 2, tinyPiece.getGlobalBounds().height / 2);
	tinyPiece.setPosition(1450, 800);
}

NPC::~NPC()
{
}

void NPC::update()
{
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(largePiece);
	t_window.draw(mediumPiece);
	t_window.draw(smallPiece);
	t_window.draw(tinyPiece);
}
