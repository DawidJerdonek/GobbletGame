/// <summary>
/// Dawid Jerdonek and Andrew Greenslade
/// 12/2022
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ xRes, yRes, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	m_grid.setupGrid();
	setupInitialPositions();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	m_grid.update(m_window);
	for (int i = 0; i < 3; i++)
	{
		m_player[i].update(m_window, m_isPlayersTurn);
	}

	snapBoardPieces();

	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::snapBoardPieces()
{
	for (int y = 0; y < m_grid.YAmountCells; y++)
	{
		for (int x = 0; x < m_grid.XAmountCells; x++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_largePiece.getPosition()) && !m_grid.cellGrid[x][y].IsOccupiedByNPC && !m_grid.cellGrid[x][y].IsOccupiedByPlayer)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_largePieceSnapped == false)
						{
							m_player[i].m_largePieceSnapped = true;
							m_player[i].m_largePiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_largePiecePreviousPos = sf::Vector2f( x,y );
							m_isPlayersTurn = false;
							moveNPC();

						}
						else if (m_player[i].m_largePieceSnapped == true)
						{
							m_player[i].m_largePiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_largePiecePreviousPos.x;
							int prevPosY = m_player[i].m_largePiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_largePiecePreviousPos = sf::Vector2f( x,y );

							m_isPlayersTurn = false;
							moveNPC();
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_mediumPiece.getPosition()) && !m_grid.cellGrid[x][y].IsOccupiedByNPC && !m_grid.cellGrid[x][y].IsOccupiedByPlayer)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_mediumPieceSnapped == false)
						{
							m_player[i].m_mediumPieceSnapped = true;
							m_player[i].m_mediumPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_mediumPiecePreviousPos = sf::Vector2f(x, y);
							m_isPlayersTurn = false;
							moveNPC();
						}
						else if (m_player[i].m_mediumPieceSnapped == true)
						{
							m_player[i].m_mediumPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_mediumPiecePreviousPos.x;
							int prevPosY = m_player[i].m_mediumPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_mediumPiecePreviousPos = sf::Vector2f(x, y);

							m_isPlayersTurn = false;
							moveNPC();
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_smallPiece.getPosition()) && !m_grid.cellGrid[x][y].IsOccupiedByNPC && !m_grid.cellGrid[x][y].IsOccupiedByPlayer)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_smallPieceSnapped == false)
						{
							m_player[i].m_smallPieceSnapped = true;
							m_player[i].m_smallPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_smallPiecePreviousPos = sf::Vector2f(x, y);
							m_isPlayersTurn = false;
							moveNPC();
						}
						else if (m_player[i].m_smallPieceSnapped == true)
						{
							m_player[i].m_smallPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_smallPiecePreviousPos.x;
							int prevPosY = m_player[i].m_smallPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_smallPiecePreviousPos = sf::Vector2f(x, y);

							m_isPlayersTurn = false;
							moveNPC();
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_tinyPiece.getPosition()) && !m_grid.cellGrid[x][y].IsOccupiedByNPC && !m_grid.cellGrid[x][y].IsOccupiedByPlayer)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_tinyPieceSnapped == false)
						{
							m_player[i].m_tinyPieceSnapped = true;
							m_player[i].m_tinyPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_tinyPiecePreviousPos = sf::Vector2f(x, y);
							m_isPlayersTurn = false;
							moveNPC();
						}
						else if (m_player[i].m_tinyPieceSnapped == true)
						{
							m_player[i].m_tinyPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_tinyPiecePreviousPos.x;
							int prevPosY = m_player[i].m_tinyPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_tinyPiecePreviousPos = sf::Vector2f(x, y);

							m_isPlayersTurn = false;
							moveNPC();
						}
					}
				}
			}
		}
	}

	/// <summary>
	///	Reset to start position is not placed on board
	/// </summary>
	for (int i = 0; i < 3; i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_largePieceSnapped == false)
		{
			m_player[i].m_largePiece.setPosition(m_player[i].m_startPosition);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_mediumPieceSnapped == false)
		{
			m_player[i].m_mediumPiece.setPosition(m_player[i].m_startPosition);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_smallPieceSnapped == false)
		{
			m_player[i].m_smallPiece.setPosition(m_player[i].m_startPosition);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_tinyPieceSnapped == false)
		{
			m_player[i].m_tinyPiece.setPosition(m_player[i].m_startPosition);
		}
		
	}
}

void Game::setupInitialPositions()
{
	/// <summary>
	/// Player Initial Positions
	/// </summary>
	m_player[0].m_largePiece.setPosition(200, 300);
	m_player[0].m_mediumPiece.setPosition(200, 300);
	m_player[0].m_smallPiece.setPosition(200, 300);
	m_player[0].m_tinyPiece.setPosition(200, 300);
	m_player[1].m_largePiece.setPosition(200, 600);
	m_player[1].m_mediumPiece.setPosition(200, 600);
	m_player[1].m_smallPiece.setPosition(200, 600);
	m_player[1].m_tinyPiece.setPosition(200, 600);
	m_player[2].m_largePiece.setPosition(200, 900);
	m_player[2].m_mediumPiece.setPosition(200, 900);
	m_player[2].m_smallPiece.setPosition(200, 900);
	m_player[2].m_tinyPiece.setPosition(200, 900);
	for (int i = 0; i < 3; i++)
	{
		m_player[i].m_startPosition = m_player[i].m_largePiece.getPosition();
	}

	/// <summary>
	/// NPC Initial Positions
	/// </summary>
	m_npc[0].m_largePiece.setPosition(1450, 300);
	m_npc[0].m_mediumPiece.setPosition(1450, 300);
	m_npc[0].m_smallPiece.setPosition(1450, 300);
	m_npc[0].m_tinyPiece.setPosition(1450, 300);
	m_npc[1].m_largePiece.setPosition(1450, 600);
	m_npc[1].m_mediumPiece.setPosition(1450, 600);
	m_npc[1].m_smallPiece.setPosition(1450, 600);
	m_npc[1].m_tinyPiece.setPosition(1450, 600);
	m_npc[2].m_largePiece.setPosition(1450, 900);
	m_npc[2].m_mediumPiece.setPosition(1450, 900);
	m_npc[2].m_smallPiece.setPosition(1450, 900);
	m_npc[2].m_tinyPiece.setPosition(1450, 900);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_grid.draw(m_window);
	for (int i = 0; i < 3; i++)
	{
		m_player[i].render(m_window);
	}
	for (int i = 0; i < 3; i++)
	{
		m_npc[i].render(m_window);
	}
	m_window.display();
}

void Game::moveNPC()
{
	bool myBool = false;

	std::pair<int, std::pair<int, int>> move = AI.minmax(m_grid, 0 , false, -1000, 1000, myBool);

	AI.finalPiece = &AI.decidePieceForMoving(m_grid, m_npc);

	Cell& cell = m_grid.cellGrid[move.second.first][move.second.second];

	AI.finalPiece->setPosition(cell.center);

	cell.IsOccupiedByNPC = true;
	AI.hasMoved = false;
	m_isPlayersTurn = true;
}
