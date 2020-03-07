#include "GreadySnake.h"
#include <cstring>

STATUS Snake::vis[][NR_ROW];
Snake::Snake() {
	srand(time(NULL));
	int x = RANDOM(INIT_LENGTH, NR_COL - 1),
		y = RANDOM(0, NR_ROW - 1);
	for (int i = 0; i < INIT_LENGTH; i++) {
		body.push_back(pos(x - i, y));
		vis[x - i][y] = true;
		display(i, (i) ? BODY_COLOR : HEAD_COLOR);
	}
	infty = false;
	curdir = DOWN;
}

void Snake::display(int i, COLORREF color)const {
	setfillcolor(color);
	solidrectangle(body[i].first*COL_WIDTH, body[i].second*ROW_HEIGHT,
		body[i].first*COL_WIDTH + BODY_SIZE, (body[i].second)*ROW_HEIGHT + BODY_SIZE);
}


bool Snake::move() {
	bool tail_flag = true;//indicate that if the tail is to be deleted
	/*insert the new head*/
	body.push_front(pos((body[0].first + d[curdir][0]+NR_COL)%(NR_COL), (body[0].second + d[curdir][1]+NR_ROW)%(NR_ROW)));

	/*if the head hit the body,return true to end the game*/
	if (bodycheck())return true;

	/*if the head hit the food,the tail won't be deleted*/
	if (foodcheck()) {
		tail_flag = false;
	}

	/*delete the tail pos if needed*/
	display(body.size() - 1, BK_COLOR);
	vis[body.back().first][body.back().second] = NONE;
	if (!infty&&tail_flag)body.pop_back();
	vis[body.front().first][body.front().second] = BODY_IN;

	display(0, HEAD_COLOR);
	display(1, BODY_COLOR);
	return false;
}

bool Snake::bodycheck()const {
	if (vis[body[0].first][body[0].second] == BODY_IN)
		return true;
	return false;
}

bool Snake::foodcheck()const {
	if (vis[body[0].first][body[0].second] == FOOD_IN)
	{
		return true;
	}
	return false;
}
void Snake::changedir(char c) {
	switch (c) {
	case 'w':
	case 'W':
		curdir = (curdir == DOWN) ? curdir : UP; break;
	case 's':
	case 'S':
		curdir = (curdir == UP) ? curdir : DOWN; break;
	case 'a':
	case 'A':
		curdir = (curdir == RIGHT) ? curdir : LEFT; break;
	case 'd':
	case 'D':
		curdir = (curdir == LEFT) ? curdir : RIGHT; break;
	default:
		break;
	}
}


Food::Food() {
	srand(time(NULL));
	int x, y;
	bool goon = true;
	while (goon) {
		x = RANDOM(0, 10 - 1), y = RANDOM(0, 5 - 1);
		if (!Snake::vis[x][y]) { goon = false; }
	}
	curpos = pos(x, y);
	Snake::vis[x][y] = FOOD_IN;
	display(curpos, FOOD_COLOR);
}

void Food::display(pos _pos, COLORREF color)const {
	setfillcolor(color);
	solidrectangle(_pos.first*COL_WIDTH, _pos.second*ROW_HEIGHT,
		_pos.first*COL_WIDTH + BODY_SIZE, (_pos.second)*ROW_HEIGHT + BODY_SIZE);
}

void Food::generate() {
	srand(time(NULL));
	int x, y;
	bool goon = true;
	while (goon) {
		x = RANDOM(0, NR_COL - 1), y = RANDOM(0, NR_ROW - 1);
		if (!Snake::vis[x][y]) { goon = false; }
	}
	curpos = pos(x, y);
	Snake::vis[x][y] = FOOD_IN;
	display(curpos, FOOD_COLOR);
}