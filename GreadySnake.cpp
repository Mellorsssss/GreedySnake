#include "GreadySnake.h"

Snake::Snake() {
	srand(time(NULL));
	int x = RANDOM(INIT_LENGTH, NR_COL - 1),
		y = RANDOM(0, NR_ROW - 1);
	for (int i = 0; i < INIT_LENGTH; i++) {
		body.push_back(pos(x - i, y));
		vis[x - i][y] = true;
		display(i, (i) ? BODY_COLOR : HEAD_COLOR);
	}
	memset(vis, 0, sizeof vis);
	infty = true;
	curdir = DOWN;
}

void Snake::display(int i, COLORREF color)const {
	setfillcolor(color);
	solidrectangle(body[i].first*COL_WIDTH, body[i].second*ROW_HEIGHT,
		body[i].first*COL_WIDTH + BODY_SIZE, (body[i].second)*ROW_HEIGHT + BODY_SIZE);
}


bool Snake::move() {
	/*delete the tail pos*/
	display(body.size() - 1, BK_COLOR);
	vis[body.back().first][body.back().second] = false;
	if (infty)body.pop_back();
	/*insert the new head*/
	body.push_front(pos(body[0].first + d[curdir][0], body[0].second + d[curdir][1]));
	/*the head hit the body*/
	if (bodycheck())return true;

	vis[body.front().first][body.front().second] = true;
	display(0, HEAD_COLOR);
	display(1, BODY_COLOR);
}

bool Snake::bodycheck()const {
	for (int i = 1; i < body.size(); i++) {
		if (body[i] == body[0])return true;
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