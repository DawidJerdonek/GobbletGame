#include "Grid.h"
#include "Cell.h"

Cell* Grid::at(int t_index)
{
	int x = t_index % XAmountCells;
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
		int x = index % XAmountCells;
		int y = index / YAmountCells;

		at(index)->x = x;
		at(index)->y = y;
		at(index)->m_id = x + (y * XAmountCells);
		

		at(index)->cellBody.setFillColor(defaultColor);

		at(index)->cellBody.setSize(sf::Vector2f((xRes / 2) / XAmountCells, yRes / YAmountCells));
		at(index)->cellBody.setPosition(offset.x + ((xRes / 2) / XAmountCells) * x, offset.y + (yRes / YAmountCells) * y);
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

void Grid::update(sf::RenderWindow &t_window)
{
	for (int y = 0; y < YAmountCells; y++)
	{
		for (int x = 0; x < XAmountCells; x++)
		{
			if (cellGrid[x][y].cellBody.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(t_window))) 
			{
				cellGrid[x][y].cellBody.setFillColor(highlightedColor);
			}
			else 
			{
				cellGrid[x][y].cellBody.setFillColor(defaultColor);
			}
		}
	}
}
