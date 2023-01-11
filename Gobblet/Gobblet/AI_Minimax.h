#pragma once
#include "Grid.h"
#include "Cell.h"
#include "NPC.h"

class AI_Minimax
{
public:
	AI_Minimax();
//	int minmax(Grid& t_grid, int t_height, int t_depth, int t_nodeindex, bool t_isPlayersTurn, std::vector<int> t_values, int t_alpha, int t_beta);
	std::pair<int, std::pair<int, int>> minmax(Grid& t_grid, int t_depth, bool t_isPlayersTurn, int t_alpha, int t_beta, bool& myBool);
	void movePiece(sf::Vector2f t_pos, Grid& t_grid, bool isPlayer);
	void unMovePiece(sf::Vector2f t_pos, Grid& t_grid);
	
	sf::CircleShape& decidePieceForMoving(Grid& t_grid, NPC t_npcs[3]);
	sf::CircleShape* finalPiece = nullptr;
	bool hasMoved = false;
	int pieceIndex = -1;

private:
	sf::Vector2f oldPos{ -1,-1 };

	std::vector<std::pair<int, int>> get_legal_moves(Grid& t_grid);
	bool board_is_full(Grid& t_grid);
	int get_board_state(Grid& t_grid);
	std::vector<std::pair<int, int>> get_occupied_positions_NPC(Grid& t_grid);
	std::vector<std::pair<int, int>> get_occupied_positions_Player(Grid& t_grid);
	bool game_is_won(std::vector<std::pair<int, int>> occupied_positions);

	std::vector<std::vector<std::pair<int, int>>> winning_states
	{
		// Every row
		{ std::make_pair(0, 0), std::make_pair(0, 1), std::make_pair(0, 2), std::make_pair(0, 3) },
		{ std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(1, 2), std::make_pair(1, 3)},
		{ std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(2, 2), std::make_pair(2, 3) },
		{ std::make_pair(3, 0), std::make_pair(3, 1), std::make_pair(3, 2), std::make_pair(3, 3) },

		// Every column
		{ std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0), std::make_pair(3, 0) },
		{ std::make_pair(0, 1), std::make_pair(1, 1), std::make_pair(2, 1), std::make_pair(3, 1) },
		{ std::make_pair(0, 2), std::make_pair(1, 2), std::make_pair(2, 2), std::make_pair(3, 2) },
		{ std::make_pair(0, 3), std::make_pair(1, 3), std::make_pair(2, 3), std::make_pair(3, 3) },

		// Every diagonal
		{ std::make_pair(0, 0), std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)  },
		{ std::make_pair(3, 0), std::make_pair(2, 1), std::make_pair(1, 2), std::make_pair(0, 3)  }
	};
};