#include "Player.h"
#include <iostream>

Player::Player()
{
	m_largePiece.setFillColor(sf::Color::White);
	m_largePiece.setRadius(100);
	m_largePiece.setOutlineThickness(2);
	m_largePiece.setOutlineColor(sf::Color::Black);
	m_largePiece.setOrigin(m_largePiece.getGlobalBounds().width / 2, m_largePiece.getGlobalBounds().height / 2);
	m_largePiece.setPosition(200, 200);

	m_mediumPiece.setFillColor(sf::Color::White);
	m_mediumPiece.setRadius(80);
	m_mediumPiece.setOutlineThickness(2);
	m_mediumPiece.setOutlineColor(sf::Color::Black);
	m_mediumPiece.setOrigin(m_mediumPiece.getGlobalBounds().width / 2, m_mediumPiece.getGlobalBounds().height / 2);
	m_mediumPiece.setPosition(200, 400);

	m_smallPiece.setFillColor(sf::Color::White);
	m_smallPiece.setRadius(60);
	m_smallPiece.setOutlineThickness(2);
	m_smallPiece.setOutlineColor(sf::Color::Black);
	m_smallPiece.setOrigin(m_smallPiece.getGlobalBounds().width / 2, m_smallPiece.getGlobalBounds().height / 2);
	m_smallPiece.setPosition(200, 600);

	m_tinyPiece.setFillColor(sf::Color::White);
	m_tinyPiece.setRadius(40);
	m_tinyPiece.setOutlineThickness(2);
	m_tinyPiece.setOutlineColor(sf::Color::Black);
	m_tinyPiece.setOrigin(m_tinyPiece.getGlobalBounds().width / 2, m_tinyPiece.getGlobalBounds().height / 2);
	m_tinyPiece.setPosition(200, 800);

}

Player::~Player()
{
}

void Player::update(sf::RenderWindow& t_window, bool& t_playersTurn)
{
	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(t_window);
	m_mouseLocation = { static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y) };

	if (t_playersTurn)
	{

		if (m_largePiece.getGlobalBounds().contains(m_mouseLocation))
		{
			if (m_largePieceSnapped == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_largePiece.setPosition(m_mouseLocation);
				}
			}
		}
		else if (m_mediumPiece.getGlobalBounds().contains(m_mouseLocation))
		{
			if (m_mediumPieceSnapped == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_mediumPiece.setPosition(m_mouseLocation);
				}
			}
		}
		else if (m_smallPiece.getGlobalBounds().contains(m_mouseLocation))
		{
			if (m_smallPieceSnapped == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_smallPiece.setPosition(m_mouseLocation);
				}
			}
		}
		else if (m_tinyPiece.getGlobalBounds().contains(m_mouseLocation))
		{
			if (m_tinyPieceSnapped == false)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_tinyPiece.setPosition(m_mouseLocation);
				}
			}
		}

		if (m_largePieceSnapped == true)
		{
			if (m_largePiece.getGlobalBounds().contains(m_mouseLocation))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_largePiece.setPosition(m_mouseLocation);
				}
			}
		}

	}
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_tinyPiece);
	t_window.draw(m_smallPiece);
	t_window.draw(m_mediumPiece);
	t_window.draw(m_largePiece);
}
