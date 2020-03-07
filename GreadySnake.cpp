#include "GreadySnake.h"
#include <cstring>

STATUS Snake::vis[][NR_ROW];
Snake::Snake()
{
	srand(time(NULL));
	headcolor = HW_COLOR[0];
	int x = RANDOM(INIT_LENGTH, NR_COL - 1),
		y = RANDOM(0, NR_ROW - 1);
	for (int i = 0; i < INIT_LENGTH; i++)
	{
		body.push_back(pos(x - i, y));
		vis[x - i][y] = true;
		display(i, (i) ? BODY_COLOR : headcolor);
	}
	infty = false;
	curdir = DOWN;
}

void Snake::display(int i, COLORREF color) const
{
	setfillcolor(color);
	solidrectangle(body[i].first * COL_WIDTH, body[i].second * ROW_HEIGHT,
				   body[i].first * COL_WIDTH + BODY_SIZE, (body[i].second) * ROW_HEIGHT + BODY_SIZE);
}

bool Snake::boundcheck(pos a) const
{
	return (a.first < NR_COL && a.first >= 0 && a.second < NR_ROW && a.second >= 0);
}

bool Snake::move(bool ok)
{
	bool tail_flag = true; //indicate that if the tail is to be deleted
	/*insert the new head*/
	if (ok)
		body.push_front(pos((body[0].first + d[curdir][0] + NR_COL) % (NR_COL), (body[0].second + d[curdir][1] + NR_ROW) % (NR_ROW)));
	else
	{
		pos newpos = pos(body[0].first + d[curdir][0], body[0].second + d[curdir][1]);
		if (boundcheck(newpos))
			body.push_front(newpos);
		else
			return true;
	}
	/*if the head hit the body,return true to end the game*/
	if (bodycheck())
		return true;

	/*if the head hit the food,the tail won't be deleted;
	moreover,change the head color if hit the 'Changecolor Food'*/

	int add;
	if (add = foodcheck())
	{
		tail_flag = false;
		score += add;
		if (add > 1)
			headcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	}

	/*delete the tail pos if needed*/
	display(body.size() - 1, BK_COLOR);
	vis[body.back().first][body.back().second] = NONE;
	if (!infty && tail_flag)
		body.pop_back();
	vis[body.front().first][body.front().second] = BODY_IN;

	display(0, headcolor);
	display(1, BODY_COLOR);
	return false;
}

bool Snake::bodycheck() const
{
	if (vis[body[0].first][body[0].second] == BODY_IN)
		return true;
	return false;
}

int Snake::foodcheck() const
{
	if (vis[body[0].first][body[0].second] == FOOD_IN)
	{
		return NORMAL_FEEDBACK;
	}
	else if (vis[body[0].first][body[0].second] == SPECIAL_IN)
	{
		return SPECIAL_FEEDBACK;
	}
	return 0;
}
void Snake::changedir(char c)
{
	switch (c)
	{
	case 'w':
	case 'W':
		curdir = (curdir == DOWN) ? curdir : UP;
		break;
	case 's':
	case 'S':
		curdir = (curdir == UP) ? curdir : DOWN;
		break;
	case 'a':
	case 'A':
		curdir = (curdir == RIGHT) ? curdir : LEFT;
		break;
	case 'd':
	case 'D':
		curdir = (curdir == LEFT) ? curdir : RIGHT;
		break;
	default:
		break;
	}
}

Food::Food()
{
	srand(time(NULL));
	int x, y;
	bool goon = true;
	while (goon)
	{
		x = RANDOM(0, NR_COL - 1), y = RANDOM(0, NR_ROW - 1);
		if (!Snake::vis[x][y])
		{
			goon = false;
		}
	}
	curpos = pos(x, y);
	Snake::vis[x][y] = FOOD_IN;
	display(curpos, FOOD_COLOR);
	cnt = 1;
}

void Food::display(pos _pos, COLORREF color) const
{
	setfillcolor(color);
	solidrectangle(_pos.first * COL_WIDTH, _pos.second * ROW_HEIGHT,
				   _pos.first * COL_WIDTH + BODY_SIZE, (_pos.second) * ROW_HEIGHT + BODY_SIZE);
}

void Food::generate()
{
	if ((Snake::vis[curpos.first][curpos.second] == SPECIAL_IN && isSpecial() && (--count >= 0)) || Snake::vis[curpos.first][curpos.second] == FOOD_IN && !isSpecial())
	{
		return;
	}
	if (isSpecial() && count <= 0)
	{
		display(curpos, BK_COLOR);
	}
	cnt++;
	if (isSpecial())
	{
		count = STEPS;
	}
	srand(time(NULL));
	int x, y;
	bool goon = true;
	while (goon)
	{
		x = RANDOM(0, NR_COL - 1), y = RANDOM(0, NR_ROW - 1);
		if (!Snake::vis[x][y])
		{
			goon = false;
		}
	}
	curpos = pos(x, y);
	Snake::vis[x][y] = (isSpecial()) ? SPECIAL_IN : FOOD_IN;
	if (isSpecial())
		display(curpos, SPECIAL_FOOD_COLOR);
	else
		display(curpos, FOOD_COLOR);
}