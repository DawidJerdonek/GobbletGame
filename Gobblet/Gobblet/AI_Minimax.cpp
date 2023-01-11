#include "AI_Minimax.h"

AI_Minimax::AI_Minimax()
{
}

std::vector<std::pair<int, int>> AI_Minimax::get_legal_moves(Grid& t_grid)
{
	std::vector<std::pair<int, int>> moves;

	for (int i = 0; i < t_grid.XAmountCells; i++)
	{
		for (int j = 0; j < t_grid.YAmountCells; j++)
		{
			if (pieceIndex < t_grid.cellGrid[i][j].pieceIndex && t_grid.cellGrid[i][j].IsOccupiedByPlayer)
			{
				moves.push_back(std::make_pair(i, j));
			}
			else
			if (!t_grid.cellGrid[i][j].IsOccupiedByNPC && !t_grid.cellGrid[i][j].IsOccupiedByPlayer)
			{
				moves.push_back(std::make_pair(i, j));
			}
		}
	}

	return moves;
}

bool AI_Minimax::board_is_full(Grid& t_grid)
{
	std::vector<std::pair<int, int>> legal_moves = get_legal_moves(t_grid);

	if (0 == legal_moves.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<std::pair<int, int>> AI_Minimax::get_occupied_positions_NPC(Grid& t_grid)
{
	std::vector<std::pair<int, int>> occupied_positions;

	for (int i = 0; i < t_grid.XAmountCells; i++)
	{
		for (int j = 0; j < t_grid.YAmountCells; j++)
		{
			if (t_grid.cellGrid[i][j].piecesOrder.size() > 0) 
			{
				if (t_grid.cellGrid[i][j].IsOccupiedByNPC && t_grid.cellGrid[i][j].piecesOrder.at(t_grid.cellGrid[i][j].piecesOrder.size() - 1).first == 1)
				{
					occupied_positions.push_back(std::make_pair(i, j));
				}
			}
		}
	}

	return occupied_positions;
}

std::vector<std::pair<int, int>> AI_Minimax::get_occupied_positions_Player(Grid& t_grid)
{
	std::vector<std::pair<int, int>> occupied_positions;

	for (int i = 0; i < t_grid.XAmountCells; i++)
	{
		for (int j = 0; j < t_grid.YAmountCells; j++)
		{
			if (t_grid.cellGrid[i][j].piecesOrder.size() > 0)
			{
				if (t_grid.cellGrid[i][j].IsOccupiedByPlayer && t_grid.cellGrid[i][j].piecesOrder.at(t_grid.cellGrid[i][j].piecesOrder.size() - 1).first == 0)
				{
					occupied_positions.push_back(std::make_pair(i, j));
				}
			}
		}
	}

	return occupied_positions;
}

int AI_Minimax::get_board_state(Grid& t_grid)
{

	std::vector<std::pair<int, int>> occupied_positions = get_occupied_positions_NPC(t_grid);

	bool is_won = game_is_won(occupied_positions);

	if (is_won)
	{
		return 1000;
	}

	occupied_positions = get_occupied_positions_Player(t_grid);
	bool is_lost = game_is_won(occupied_positions);

	if (is_lost)
	{
		return -1000;
	}

	bool is_full = board_is_full(t_grid);
	if (is_full)
	{
		return 0;
	}

	return 0;
}

bool AI_Minimax::game_is_won(std::vector<std::pair<int, int>> occupied_positions)
{
	bool game_won;

	for (int i = 0; i < winning_states.size(); i++)
	{
		game_won = true;
		std::vector<std::pair<int, int>> curr_win_state = winning_states[i];
		
		for (int j = 0; j < 4; j++)
		{
			if (!(std::find(std::begin(occupied_positions), std::end(occupied_positions), curr_win_state[j]) != std::end(occupied_positions)))
			{
				game_won = false;
				break;
			}
		}

		if (game_won)
		{
			break;
		}
	}
	return game_won;
}

std::pair<int, std::pair<int, int>> AI_Minimax::minmax(Grid& t_grid, int t_depth, bool t_isPlayersTurn, int t_alpha, int t_beta, bool& myBool)
{
	std::pair<int, int> best_move = std::make_pair(-1, -1);
	int best_score = (t_isPlayersTurn == false) ? -1000 : 1000;

	//if no moves left
	if (board_is_full(t_grid) || 0 != get_board_state(t_grid))
	{
		myBool = true;
		best_score = get_board_state(t_grid);
		return std::make_pair(best_score, best_move);
	}

	std::vector<std::pair<int, int>> legal_moves;

	if (!myBool) 
	{
		legal_moves = get_legal_moves(t_grid);
	}

	for (int i = 0; i < legal_moves.size(); i++)
	{
		std::pair<int, int> curr_move = legal_moves[i];

		movePiece(sf::Vector2f(curr_move.first, curr_move.second), t_grid, t_isPlayersTurn);

		if (!t_isPlayersTurn)
		{
			int score = minmax(t_grid, t_depth + 1, true ,t_alpha, t_beta, myBool).first;

			if (best_score < score)
			{
				best_score = score - t_depth * 3;
				best_move = curr_move;

				t_alpha = std::max(t_alpha, best_score);
				unMovePiece(sf::Vector2f(curr_move.first, curr_move.second), t_grid);

				if (t_beta <= t_alpha)
				{
					break;
				}
			}
		}
		else
		{
			int score = minmax(t_grid, t_depth + 1, false, t_alpha, t_beta, myBool).first;

			if (best_score > score)
			{
				best_score = score + t_depth * 3;
				best_move = curr_move;

				t_beta = std::min(t_beta, best_score);
				unMovePiece(sf::Vector2f(curr_move.first, curr_move.second), t_grid);

				if (t_beta <= t_alpha)
				{
					break;
				}
			}

		}
		unMovePiece(sf::Vector2f(curr_move.first, curr_move.second), t_grid);
	}

	return std::make_pair(best_score, best_move);
}

void AI_Minimax::movePiece(sf::Vector2f t_pos, Grid& t_grid, bool isPlayer)
{
	if (t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].pieceIndex > pieceIndex)
	{
		t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].IsOccupiedByPlayer = false;
	}

	if (isPlayer) 
	{
		t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].IsOccupiedByPlayer = true;
	}
	else {
		t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].IsOccupiedByNPC = true;
	}
}

void AI_Minimax::unMovePiece(sf::Vector2f t_pos, Grid& t_grid)
{
	t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].IsOccupiedByPlayer = false;
	t_grid.cellGrid[(int)t_pos.x][(int)t_pos.y].IsOccupiedByNPC = false;
}

sf::CircleShape& AI_Minimax::decidePieceForMoving(Grid& t_grid, NPC t_npcs[3])
{
	sf::CircleShape* t_circleShape = nullptr;
	pieceIndex = -1;
	npcIndex = -1;

	for (int pieceToMove = 0; pieceToMove < 4; pieceToMove++)
	{
		if (hasMoved)
		{
			break;
		}

		switch (pieceToMove)
		{
		case 0:
			for (int i = 0; i < 3; i++)
			{
				if (hasMoved)
				{
					break;
				}

				switch (t_npcs[i].largePieceInPlay)
				{
				case false:
					oldPos = t_npcs[i].largePieceBoardCoords;
					t_circleShape = &t_npcs[i].m_largePiece;
					t_npcs[i].largePieceInPlay = true;
					hasMoved = true;
					pieceIndex = 0;
					npcIndex = i;
					break;
				default:
					break;
				}
			}
			break;
		case 1:
			for (int i = 0; i < 3; i++)
			{
				if (hasMoved)
				{
					break;
				}

				switch (t_npcs[i].mediumPieceInPlay)
				{
				case false:
					oldPos = t_npcs[i].mediumPieceBoardCoords;
					t_circleShape = &t_npcs[i].m_mediumPiece;
					t_npcs[i].mediumPieceInPlay = true;
					hasMoved = true;
					pieceIndex = 1;
					npcIndex = i;
					break;
				default:
					break;
				}
			}
			break;
		case 2:
			for (int i = 0; i < 3; i++)
			{
				if (hasMoved)
				{
					break;
				}

				switch (t_npcs[i].smallPieceInPlay)
				{
				case false:
					oldPos = t_npcs[i].smallPieceBoardCoords;
					t_circleShape = &t_npcs[i].m_smallPiece;
					t_npcs[i].smallPieceInPlay = true;
					hasMoved = true;
					pieceIndex = 2;
					npcIndex = i;
					break;
				default:
					break;
				}
			}
			break;
		case 3:
			for (int i = 0; i < 3; i++)
			{
				if (hasMoved)
				{
					break;
				}

				switch (t_npcs[i].tinyPieceInPlay)
				{
				case false:
					oldPos = t_npcs[i].tinyPieceBoardCoords;
					t_circleShape = &t_npcs[i].m_tinyPiece;
					t_npcs[i].tinyPieceInPlay = true;
					hasMoved = true;
					pieceIndex = 3;		
					npcIndex = i;
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}

		if (t_circleShape != nullptr)
		{
			return *t_circleShape;
		}
	}
}