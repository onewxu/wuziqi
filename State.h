#pragma once
#include "Board.h"

class State
{
	Board board;
	//int player;
	int last_move;
	int moved;

public:
	State();

	State(vector<char> v);

	~State();

	void print_state();

	int make_move(int m, int player);

	int is_end();

	vector<char> get_legal_moves();

	bool is_valid(int p);
};

