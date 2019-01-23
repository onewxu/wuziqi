#include "stdafx.h"
#include "State.h"

extern const int DRAW = 0;
extern const int NOT_DETERMINED = 2;

State::State() {
	board = Board();
	last_move = -1;
	moved = 0;
}

State::State(vector<char> v) {
	board = Board(v);
	last_move = -1;
	moved = 0;
}

State::~State() {

}

void State::print_state() {
	board.print_board();
}

int State::make_move(int m, int player) {
	if (board.move(m, player)) {
		last_move = m;
		moved++;
	}
	return last_move;
}

int State::is_end() {
	int t = board.who_wins(last_move); // +1, -1 for winner, 0 for draw, 2 for not end
	if (t != 0) return t;
	if (moved == board.size()) return DRAW; //
	return NOT_DETERMINED; //NOT_DETERMINED
}

vector<char> State::get_legal_moves() {
	vector<char> ret;
	for (int i = 0; i < board.size(); i++) {
		if (board.getv(i) == 0) {
			ret.push_back(i);
		}
	}
	return ret;
}

bool State::is_valid(int p) {
	return board.getv(p) == 0;
}
