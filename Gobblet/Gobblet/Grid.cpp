#include "Grid.h"
#include "Cell.h"

Cell* Grid::at(int t_index)
{
	int x = t_index % xAmountCells;
	int y = t_index / YAmountCells;

	return &cellGrid[x][y];
}

Grid::Grid()
{

}

Grid::~Grid()
{

}

void Grid::setupGrid()
{
	if (!idFont.loadFromFile("ASSETS\\FONTS\\NotoSansSymbols-VariableFont_wght.ttf"))
	{
		std::cout << "Error with fonts" << std::endl;
	}

	bool _isBlack = false;

	for (int index = 0; index < TotalCells; index++)
	{
		int x = index % xAmountCells;
		int y = index / YAmountCells;

		at(index)->x = x;
		at(index)->y = y;
		at(index)->m_id = x + (y * xAmountCells);
		

		at(index)->cellBody.setFillColor(sf::Color(150,78,0,255));

		at(index)->cellBody.setSize(sf::Vector2f(xRes / xAmountCells - 50, yRes / YAmountCells - 50));
		at(index)->cellBody.setPosition((xRes / xAmountCells) * x + 25, (yRes / YAmountCells) * y + 25);
		at(index)->idText.setPosition(at(index)->cellBody.getPosition());
		at(index)->center = sf::Vector2f(at(index)->cellBody.getPosition().x + (at(index)->cellBody.getGlobalBounds().width / 2), at(index)->cellBody.getPosition().y + (at(index)->cellBody.getGlobalBounds().height / 2));
		at(index)->idText.setFont(idFont);
		at(index)->idText.setCharacterSize(40);
		at(index)->idText.setString(std::to_string(at(index)->getID()));

	}
}

Cell* Grid::GetIntersects(sf::Vector2f pos)
{
	for (int c = 0; c < TotalCells; c++)
	{
		Cell* cl = at(c);

		if (cl->cellBody.getGlobalBounds().contains(pos))
		{
			return cl;
		}
	}

	return nullptr;
}

void Grid::draw(sf::RenderWindow& m_window)
{
	for (int c = 0; c < TotalCells; c++)
	{
		m_window.draw(at(c)->cellBody);
		m_window.draw(at(c)->idText);
	}
}

void Grid::reset()
{

}