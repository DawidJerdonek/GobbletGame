/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Player.h"
#include "NPC.h"
#include "GLOBALS.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void snapBoardPieces();
	void setupInitialPositions();
	void render();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
	bool m_isPlayersTurn = true;

	Grid m_grid;

	Player m_player[3];//3 sets of sized pieces


	NPC m_npc[3];//3 sets of sized pieces
};

#endif // !GAME_HPP

