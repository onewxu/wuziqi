#include "stdafx.h"
#include "MCTS.h"

MCTS::MCTS() {
	root = new Node();
	root->make_children();
}

MCTS::MCTS(State s) {
	root = new Node(s);
	root->make_children();
}

MCTS::~MCTS() {

}

Node * MCTS::select() {
	return root->max_uct();
}

Node * MCTS::select(Node * n) {
	return n->max_uct();
}

void MCTS::expand(Node * n) {
	if (n->is_leaf() == false) {
		return;
	}
	n->make_children();
}

int MCTS::rollout(Node * leaf) {
	/*State s = leaf->get
	Node * p = leaf;
	Node * ch = p->make_random_child();
	while (ch != NULL) {
	p = ch;
	ch = p->make_random_child();
	}

	return p;*/
	int reward = leaf->simulate();
	return reward;
}

void MCTS::update(Node * leaf, int reward) {
	//while(terminal != leaf)
	leaf->backprop(reward);
}

void MCTS::exec() {
	Node * tmp = root;
	while (!tmp->is_leaf()) {
		tmp = tmp->max_uct();
	}
	if (tmp->get_vtimes() != 0) {
		bool result = tmp->make_children();
		if (result) {
			tmp = tmp->max_uct();
		}
	}
	tmp->backprop(tmp->simulate());
}

bool MCTS::is_valid_move(int i) {
	return root->get_state().is_valid(i);
}

void MCTS::make_robot_move() {
	Node * tmp = root->max_vtimes();
	clean_tree(root, tmp);
	root = tmp;
	root->parent = NULL;
	root->get_state().print_state();
}

void MCTS::make_human_move(int i) {
	Node * tmp = root->get_child(i);
	clean_tree(root, tmp);
	root = tmp;
	root->parent = NULL;
	root->get_state().print_state();
}

int MCTS::game_end() {
	return root->get_state().is_end();
}

void MCTS::clean_tree(Node * root, Node * node) {
	if (root == NULL || root == node) return;
	for (auto ch : root->children) {
		clean_tree(ch, node);
	}
	delete root;
	root = NULL;
}
