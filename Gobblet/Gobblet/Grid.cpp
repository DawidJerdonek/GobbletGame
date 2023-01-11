#include "Grid.h"
#include "Cell.h"

//gets a cell at certain index
Cell* Grid::at(int t_index)
{
	int x = t_index % XAmountCells;
	int y = t_index / YAmountCells;

	return &cellGrid[x][y];
}

//constructer
Grid::Grid()
{

}

//deconstructer
Grid::~Grid()
{

}

/// <summary>
/// Sets up grid with information such as each cells location, color, size, etc.
/// </summary>
void Grid::setupGrid()
{
	//gets font for each cells id
	if (!idFont.loadFromFile("ASSETS\\FONTS\\NotoSansSymbols-VariableFont_wght.ttf"))
	{
		std::cout << "Error with fonts" << std::endl;
	}

	//loops through each cell for setting up
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

//gets a cell at a pixels coordinates
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

//draws each cell in the grid
void Grid::draw(sf::RenderWindow& m_window)
{
	for (int c = 0; c < TotalCells; c++)
	{
		m_window.draw(at(c)->cellBody);
		m_window.draw(at(c)->idText);
	}
}

//updates color if hovering over cell a darker shade of brown
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