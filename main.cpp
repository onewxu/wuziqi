// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MCTS.h"

//const int DRAW = 0;
//const int NOT_DETERMINED = 2;

int main()
{
	int width = 7;
	cout << "Welcome to WZQ world!" << endl;
	vector<char> vec = vector<char>(width*width, 0);
	State state = State(vec);
	state.print_state();
	int first = 0;
	cout << "who plays first: 1(robot), 2(humanoid)" << endl;
	cin >> first;
	while (first != 1 && first != 2) {
		cout << "error input..." << endl;
		cin >> first;
	}
	int r = -1, c = -1;
	MCTS mcts(state);
	int max_thinking = 100000;
	while (1) {
		if (first == 1) {
			cout << "robot is thinking!" << endl;
			for (int i = 0; i < max_thinking; i++) {
				mcts.exec();
				if (i % (max_thinking / 10) == 0) {
					cout << "*";
				}
			}
			cout << endl;
			mcts.make_robot_move();
			//mcts.get_root()->get_state().print_state();
			first = 2;
		}
		else {
			cout << "ok, it's your turn, please enter: row column, e.g. 0 1" << endl;
			cin >> r >> c;
			while (1) {
				if (r >= 0 && r < width && c >= 0 && c < width) {
					if (mcts.is_valid_move(r * width + c)) break;
				}
				cout << "error input..." << endl;
				cin >> r >> c;
			}
			mcts.make_human_move(r * width + c);
			first = 1;
		}
		int r = mcts.game_end();
		if (r != 2) { //NOT_DETERMINED
			cout << "game_ended: ";
			if (r == 0) { //DRAW
				cout << "draw.";
			}
			else if (first == 2) {
				cout << "robot win.";
			}
			else {
				cout << "humanoid win.";
			}
			cout << " gg~~" << endl;
			break;
		}
	}
	int a;
	cin >> a;
    return 0;
}

