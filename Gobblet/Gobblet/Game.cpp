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
	m_window{ sf::VideoMode{ xRes, yRes, 32U }, "Gobblet Game" },
	m_exitGame{false} //when true game will exit
{
	//Load Font from File
	if (!m_font.loadFromFile("Assets/Fonts/ariblk.ttf"))
	{
		std::cout << "error with font file file";
	}
	m_loseWinText.setFont(m_font);
	m_loseWinText.setCharacterSize(50);
	m_loseWinText.setPosition(10,20);

	//setup the board
	m_grid.setupGrid();
	//Set Initial Piece Positions
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
	if (m_state == MENU)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			m_difficulty = -1;
			m_state = GAME;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			m_difficulty = 100;
			m_state = GAME;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			m_difficulty = 250;
			m_state = GAME;
		}

	}
	if (m_state == GAME)
	{

	}
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
	if (m_state == MENU)
	{

	}
	if (m_state == GAME)
	{
		if (m_gameWon == false && m_gameLost == false)
		{
			m_grid.update(m_window);
			for (int i = 0; i < 3; i++)
			{
				m_player[i].update(m_window, m_isPlayersTurn);
			}

			if (AI.get_board_state(m_grid) == -1000) {
				m_gameWon = true;
			}
			else if(AI.get_board_state(m_grid) == 1000) {
				m_gameLost = true;
			}

			snapBoardPieces();
		}

		if (m_gameWon)
		{
			m_loseWinText.setFillColor(sf::Color::Green);
			m_loseWinText.setString("You have WON! \n Press 'ESCAPE' to quit game");
		}
		else if (m_gameLost)
		{
			m_loseWinText.setFillColor(sf::Color::Red);
			m_loseWinText.setString("You have been defeated! \n Press 'ESCAPE' to quit game");
		}
	}
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
				if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_largePiece.getPosition()))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_largePieceSnapped == false && 0 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_largePieceSnapped = true;
							m_player[i].m_largePiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_largePiecePreviousPos = sf::Vector2f( x,y );
							m_grid.cellGrid[x][y].pieceIndex = 0;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 0)));
							m_isPlayersTurn = false;
							moveNPC();
							break;
						}
						else if (m_player[i].m_largePieceSnapped == true && 0 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_largePiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_largePiecePreviousPos.x;
							int prevPosY = m_player[i].m_largePiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_largePiecePreviousPos = sf::Vector2f( x,y );
							m_grid.cellGrid[x][y].pieceIndex = 0;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 0)));
							m_isPlayersTurn = false;
							m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.erase(std::remove(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.begin(), m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.end(), std::make_pair(0, std::make_pair(i, 0))));
							
							if (m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() > 0) 
							{
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.at(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() - 1).second.second;
							}
							else {
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = -1;
							}
							
							moveNPC();
							break;
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_mediumPiece.getPosition()))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{	
						checkForNPCUnderCell(x, y);

						if (m_player[i].m_mediumPieceSnapped == false && 1 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_mediumPieceSnapped = true;
							m_player[i].m_mediumPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_mediumPiecePreviousPos = sf::Vector2f(x, y);
							m_grid.cellGrid[x][y].pieceIndex = 1;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 1)));
							m_isPlayersTurn = false;
							moveNPC();
							break;
						}
						else if (m_player[i].m_mediumPieceSnapped == true && 1 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_mediumPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_mediumPiecePreviousPos.x;
							int prevPosY = m_player[i].m_mediumPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_mediumPiecePreviousPos = sf::Vector2f(x, y);
							m_grid.cellGrid[x][y].pieceIndex = 1;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0 ,std::make_pair(i, 1)));
							m_isPlayersTurn = false;
							m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.erase(std::remove(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.begin(), m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.end(), std::make_pair(0, std::make_pair(i, 1))));
							
							if (m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() > 0)
							{
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.at(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() - 1).second.second;
							}
							else {
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = -1;
							}

							moveNPC();
							break;
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_smallPiece.getPosition()))
				{

					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_smallPieceSnapped == false && 2 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_smallPieceSnapped = true;
							m_player[i].m_smallPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_smallPiecePreviousPos = sf::Vector2f(x, y);
							m_isPlayersTurn = false;
							m_grid.cellGrid[x][y].pieceIndex = 2;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 2)));
							moveNPC();
							break;
						}
						else if (m_player[i].m_smallPieceSnapped == true && 2 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_smallPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_smallPiecePreviousPos.x;
							int prevPosY = m_player[i].m_smallPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_smallPiecePreviousPos = sf::Vector2f(x, y);
							m_grid.cellGrid[x][y].pieceIndex = 2;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 2)));
							m_isPlayersTurn = false;
							m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.erase(std::remove(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.begin(), m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.end(), std::make_pair(0, std::make_pair(i, 2))));
							
							if (m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() > 0)
							{
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.at(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() - 1).second.second;
							}
							else {
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = -1;
							}

							moveNPC();
							break;
						}
					}
				}
				else if (m_grid.cellGrid[x][y].cellBody.getGlobalBounds().contains(m_player[i].m_tinyPiece.getPosition()))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
					{
						if (m_player[i].m_tinyPieceSnapped == false && 3 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_tinyPieceSnapped = true;
							m_player[i].m_tinyPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;
							m_player[i].m_tinyPiecePreviousPos = sf::Vector2f(x, y);
							m_isPlayersTurn = false;
							m_grid.cellGrid[x][y].pieceIndex = 3;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 3)));
							moveNPC();
							break;
						}
						else if (m_player[i].m_tinyPieceSnapped == true && 3 != m_grid.cellGrid[x][y].pieceIndex)
						{
							checkForNPCUnderCell(x, y);

							m_player[i].m_tinyPiece.setPosition(m_grid.cellGrid[x][y].center.x, m_grid.cellGrid[x][y].center.y);
							m_grid.cellGrid[x][y].IsOccupiedByPlayer = true;

							//Set new Previous
							int prevPosX = m_player[i].m_tinyPiecePreviousPos.x;
							int prevPosY = m_player[i].m_tinyPiecePreviousPos.y;
							m_grid.cellGrid[prevPosX][prevPosY].IsOccupiedByPlayer = false;
							m_player[i].m_tinyPiecePreviousPos = sf::Vector2f(x, y);
							m_grid.cellGrid[x][y].pieceIndex = 3;
							m_grid.cellGrid[x][y].piecesOrder.push_back(std::make_pair(0, std::make_pair(i, 3)));
							m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.erase(std::remove(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.begin(), m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.end(), std::make_pair(0, std::make_pair(i, 3))));
							m_isPlayersTurn = false;
							
							if (m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() > 0)
							{
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.at(m_grid.cellGrid[prevPosX][prevPosY].piecesOrder.size() - 1).second.second;
							}
							else {
								m_grid.cellGrid[prevPosX][prevPosY].pieceIndex = -1;
							}

							moveNPC();
							break;
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
		else
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_mediumPieceSnapped == false)
		{
			m_player[i].m_mediumPiece.setPosition(m_player[i].m_startPosition);
		}
		else
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_smallPieceSnapped == false)
		{
			m_player[i].m_smallPiece.setPosition(m_player[i].m_startPosition);
		}
		else
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && m_player[i].m_tinyPieceSnapped == false)
		{
			m_player[i].m_tinyPiece.setPosition(m_player[i].m_startPosition);
		}
		
	}
}

void Game::checkForNPCUnderCell(int x, int y)
{
	for (int i = 0; i < m_grid.cellGrid[x][y].piecesOrder.size(); i++)
	{
		if (m_grid.cellGrid[x][y].piecesOrder.at(i).first == 1)
		{
			switch (m_grid.cellGrid[x][y].piecesOrder.at(i).second.second)
			{
			case 1:
				m_npc[m_grid.cellGrid[x][y].piecesOrder.at(i).second.first].m_mediumPiece.setPosition(sf::Vector2f(-100, -100));
				break;
			case 2:
				m_npc[m_grid.cellGrid[x][y].piecesOrder.at(i).second.first].m_smallPiece.setPosition(sf::Vector2f(-100, -100));
				break;
			case 3:
				m_npc[m_grid.cellGrid[x][y].piecesOrder.at(i).second.first].m_tinyPiece.setPosition(sf::Vector2f(-100, -100));
				break;
			default:
				break;
			}
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
	if (m_state == MENU)
	{

		m_menu.render(m_window);

	}

	if (m_state == GAME)
	{
		m_grid.draw(m_window);
		for (int i = 0; i < 3; i++)
		{
			m_player[i].render(m_window);
		}
		for (int i = 0; i < 3; i++)
		{
			m_npc[i].render(m_window);
		}
		m_window.draw(m_loseWinText);
	}
	m_window.display();
}

void Game::moveNPC()
{
	if (!m_isPlayersTurn && !m_gameWon && !m_gameLost)
	{
		bool myBool = false;

		AI.finalPiece = &AI.decidePieceForMoving(m_grid, m_npc);

		std::pair<int, std::pair<int, int>> move = AI.minmax(m_grid, m_difficulty, false, -1000, 1000, myBool);

		Cell& cell = m_grid.cellGrid[move.second.first][move.second.second];

		AI.finalPiece->setPosition(cell.center);

		m_grid.cellGrid[move.second.first][move.second.second].piecesOrder.push_back(std::make_pair(1, std::make_pair(AI.npcIndex, AI.pieceIndex)));

		AI.pieceIndex = -1;
		AI.npcIndex = -1;
		cell.IsOccupiedByNPC = true;
		AI.hasMoved = false;
		m_isPlayersTurn = true;
	}
}
