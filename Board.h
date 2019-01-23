#pragma once
#include "stdafx.h"

class Board
{
	vector<char> value;
	int n;

public:
	Board();

	Board(vector<char> s);

	~Board();

	void print_board();

	int size();

	bool move(int i, int player);

	int who_wins(int l);

	int getv(int i);
};

