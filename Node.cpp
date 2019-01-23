#include "stdafx.h"
#include "Node.h"

const int DRAW = 0;
const int NOT_DETERMINED = 2;
default_random_engine generator;

Node::Node(State s, int player, Node * parent) {
	this->state = s;
	this->player = player;
	this->parent = parent;
	this->children = {};
	this->score = 0;
	this->vtimes = 0;
}

Node::~Node()
{
}

bool Node::is_leaf() {
	return children.size() == 0;
}

int Node::get_vtimes() {
	return vtimes;
}

int Node::get_score() {
	return score;
}

bool Node::make_children() {
	if (state.is_end() != NOT_DETERMINED) { //
		return false;
	}
	vector<char> legal_moves = state.get_legal_moves();
	for (auto e : legal_moves) {
		State s = state;
		s.make_move(e, player);
		children.push_back(new Node(s, -player, this));
	}
	return true;
}

Node * Node::max_uct() {
	double max = -10;
	Node * ret = NULL;
	for (auto ch : children) {
		if (ch->vtimes == 0) {
			return ch;
		}
		double tmp = (ch->score + 0.0) / ch->vtimes + sqrt(log(vtimes) / ch->vtimes);
		if (tmp > max) {
			max = tmp;
			ret = ch;
		}
	}
	return ret;
}

Node * Node::max_vtimes() {
	int max = -10;
	Node * ret = NULL;
	for(auto ch : children) {
		if (ch->vtimes > max) {
			max = ch->vtimes;
			ret = ch;
		}
	}
	return ret;
}

/*Node * Node::make_random_child() {
if (state.is_end() != NOT_DETERMINED) {
return NULL;
}
vector<int> legal_moves = state.get_legal_moves();
State s = state;
uniform_int_distribution<int> distribution(0, legal_moves.size()-1);
int e = distribution(generator);
s.make_move(legal_moves[e], player);
Node * ret = new Node(s, -player, this);
s.print_state();
children.push_back(ret);
return ret;
}*/

int Node::simulate() {
	State s = state;
	int reward = state.is_end();
	int p = player;
	while (reward == NOT_DETERMINED) { 
		vector<char> legal_moves = s.get_legal_moves();
		uniform_int_distribution<int> distribution(0, legal_moves.size() - 1);
		int e = distribution(generator);
		s.make_move(legal_moves[e], p);
		reward = s.is_end();
		p = -p;
		//s.print_state();
	}
	return reward;
}

void Node::backprop(int reward) {
	Node * tmp = this;
	while (tmp != NULL) {
		tmp->vtimes++;
		tmp->score += tmp->player == 1 ? -reward : reward;
		tmp = tmp->parent;
	}
}

State Node::get_state() {
	return state;
}

Node * Node::get_child(int i) {
	for (auto ch : children) {
		if (ch->get_state().is_valid(i) == false) {
			return ch;
		}
	}
	return NULL;
}


	
