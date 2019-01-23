#include "stdafx.h"
#include "Board.h"

Board::Board(){
	n = 7;/******************board size*************/
	value = vector<char>(n*n, 0);
}

Board::Board(vector<char> s) {
	//n = 7;/******************board size*************/
	value = s;
	n = (int)sqrt(s.size());
	if (n * n != s.size()) {
		exit(1);
	}
}

Board::~Board()
{
}

void Board::print_board() {
	for (size_t i = 0; i < value.size(); i++) {
		if (value[i] < 0) {
			cout << "x" << " ";
		}
		else if (value[i] > 0) {
			cout << "1" << " ";
		}
		else {
			cout << "0" << " ";
		}
		
		if (i % n == n - 1) {
			cout << endl;
		}
	}
	cout << endl;
}

int Board::size() {
	return n*n;
}

bool Board::move(int i, int player) {
	if (i < 0 || i >= n*n) {
		return false;
	}
	if (value[i] != 0) {
		return false;
	}
	value[i] = player;
	return true;
}

int Board::who_wins(int last) {/********type of game******************/
	//tic tac toe
	/*if (l >= 0 && value[l] == 0) return value[l];
	for (int i = 0; i < n; i++) {
		if (value[i] == value[i + 3] && value[i] == value[i + 6]) return value[i];
		int j = n * i;
		if (value[j] == value[j + 1] && value[j] == value[j + 2]) return value[j];
	}
	if (l % 4 == 0) {
		if (value[0] == value[4] && value[0] == value[8]) {
			return value[4];
		}
	}
	if (l == 2 || l == 4 || l == 6) {
		if (value[2] == value[4] && value[2] == value[6]) {
			return value[4];
		}
	}*/

	//wuziqi
	if (last < 0 || value[last] == 0) return 0;
	int r = last / n;
	int c = last % n;
	
	///////////////check column direction
	int count = 1;
	int inc = n, tmp = last;
	for (int i = r + 1; i < n; i++) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	inc = -n, tmp = last;
	for (int i = r - 1; i >= 0; i--) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count > 4) {
		return value[last];
	} 

	///////////////////////////////////check row direction
	count = 1;
	inc = 1, tmp = last;
	for (int i = c + 1; i < n; i++) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	inc = -1, tmp = last;
	for (int i = c - 1; i >= 0; i--) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count > 4) {
		return value[last];
	}

	///////////////////////////////////check southeast direction
	count = 1;
	inc = n+1, tmp = last;
	for (int i = c + 1, j = r + 1; i < n && j < n; i++, j ++) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	inc = -n-1, tmp = last;
	for (int i = c - 1, j = r - 1; i >= 0 && j >= 0; i--, j--) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count > 4) {
		return value[last];
	}

	///////////////////////////////////check northeast direction
	count = 1;
	inc = n - 1, tmp = last;
	for (int i = c - 1, j = r + 1; i >= 0 && j < n; i--, j++) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	inc = 1 - n, tmp = last;
	for (int i = c + 1, j = r - 1; i < n && j >= 0; i++, j--) {
		tmp += inc;
		if (value[last] == value[tmp]) {
			count++;
		}
		else {
			break;
		}
	}
	if (count > 4) {
		return value[last];
	}

	return 0;
}

int Board::getv(int i) {
	return value[i];
}
