#include "SnakeGame.h"
using namespace std;

int main() {
	initgraph(640, 480);
	SnakeGame* MainLoop = new SnakeGame;
	MainLoop->menu();
	return 0;
}