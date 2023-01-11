#include <iostream>
#include <SFML\Graphics.hpp>
#include "Grid.h"
#include "GLOBALS.h"

#pragma once
/// <summary>
/// The main SFML menu
/// </summary>
class Menu
{
public:

	Menu();
	void render(sf::RenderWindow& t_window);

private:

	sf::Font m_font;
	sf::Text m_title;
	sf::Text m_difficultyChoice;
};

