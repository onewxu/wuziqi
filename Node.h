#pragma once
#include "State.h"

class Node
{
public:
	Node * parent;
	vector<Node *> children;
	int score;
	int vtimes;
	int player;
	State state;

public:
	Node(State s = State(), int player = 1, Node * parent = NULL);

	~Node();

	bool is_leaf();

	int get_vtimes();

	int get_score();

	bool make_children();

	Node * max_uct();

	Node * max_vtimes();

	int simulate();

	void backprop(int reward);

	State get_state();

	Node * get_child(int i);
};

