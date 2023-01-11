#include "Menu.h"

Menu::Menu()
{
	//Load Font from File
	if (!m_font.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}

	//Setup Font text
	m_title.setFont(m_font);
	m_title.setCharacterSize(100);
	m_title.setPosition(500, 20);
	m_title.setFillColor(sf::Color::Yellow);
	m_title.setString("Gobblet");

	//Setup Difficulty text
	m_difficultyChoice.setFont(m_font);
	m_difficultyChoice.setCharacterSize(50);
	m_difficultyChoice.setPosition(500, 200);
	m_difficultyChoice.setFillColor(sf::Color::Blue);
	m_difficultyChoice.setString("Press '1' to choose Easy Difficulty \n\nPress '2' to choose Medium Difficulty \n\nPress '3' to choose Hard Difficulty");
}

void Menu::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_title);
	t_window.draw(m_difficultyChoice);
}
