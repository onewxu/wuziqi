#pragma once
#include "node.h"

class MCTS
{
public:
	Node * root;

public:
	MCTS();

	MCTS(State s);

	~MCTS();

	Node * select();

	Node * select(Node * n);

	void expand(Node * n);

	int rollout(Node * leaf);

	void update(Node * leaf, int reward);

	void exec();

	bool is_valid_move(int i);

	void make_robot_move();

	void make_human_move(int i);

	int game_end();

	void clean_tree(Node * root, Node * node);
};

