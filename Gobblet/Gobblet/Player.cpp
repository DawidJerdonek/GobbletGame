#include "Player.h"
#include <iostream>

Player::Player()
{
	largePiece.setFillColor(sf::Color::White);
	largePiece.setRadius(100);
	largePiece.setOutlineThickness(2);
	largePiece.setOutlineColor(sf::Color::Black);
	largePiece.setOrigin(largePiece.getGlobalBounds().width / 2, largePiece.getGlobalBounds().height / 2);
	largePiece.setPosition(200, 200);

	mediumPiece.setFillColor(sf::Color::White);
	mediumPiece.setRadius(80);
	mediumPiece.setOutlineThickness(2);
	mediumPiece.setOutlineColor(sf::Color::Black);
	mediumPiece.setOrigin(mediumPiece.getGlobalBounds().width / 2, mediumPiece.getGlobalBounds().height / 2);
	mediumPiece.setPosition(200, 400);

	smallPiece.setFillColor(sf::Color::White);
	smallPiece.setRadius(60);
	smallPiece.setOutlineThickness(2);
	smallPiece.setOutlineColor(sf::Color::Black);
	smallPiece.setOrigin(smallPiece.getGlobalBounds().width / 2, smallPiece.getGlobalBounds().height / 2);
	smallPiece.setPosition(200, 600);

	tinyPiece.setFillColor(sf::Color::White);
	tinyPiece.setRadius(40);
	tinyPiece.setOutlineThickness(2);
	tinyPiece.setOutlineColor(sf::Color::Black);
	tinyPiece.setOrigin(tinyPiece.getGlobalBounds().width / 2, tinyPiece.getGlobalBounds().height / 2);
	tinyPiece.setPosition(200, 800);
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(largePiece);
	t_window.draw(mediumPiece);
	t_window.draw(smallPiece);
	t_window.draw(tinyPiece);
}
