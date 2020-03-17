#include "GreadySnake.h"

STATUS Snake::vis[][NR_ROW]; //the status are:NONE,BODY_IN,FOOD_IN,SPECIAL_IN

/*default constructor,init the pos of the snake and draw it for the first time*/
Snake::Snake()
{
	srand(time(NULL));
	headcolor = HW_COLOR[0];
	int x = RANDOM(INIT_LENGTH, NR_COL - 1), //make sure the body won't be out of range
		y = RANDOM(0, NR_ROW - 1);
	/*draw the body for the first time*/
	for (int i = 0; i < INIT_LENGTH; i++)
	{
		body.push_back(pos(x - i, y));
		vis[x - i][y] = true;
		display(i, (i) ? BODY_COLOR : headcolor); //set the color
	}
	curdir = DOWN; //the dir
}

/*the func to draw
 * input :the pos to draw,the color to show
 * output:null
*/
void Snake::display(int i, COLORREF color) const
{
	setfillcolor(color);
	solidrectangle(body[i].first * COL_WIDTH, body[i].second * ROW_HEIGHT,
		body[i].first * COL_WIDTH + BODY_SIZE, (body[i].second) * ROW_HEIGHT + BODY_SIZE);
}

/*check the boundry
 *input:the pos to check
 *output:return true if the head is out of range
*/
bool Snake::boundcheck(pos a) const
{
	return (a.first < NR_COL && a.first >= 0 && a.second < NR_ROW && a.second >= 0);
}

/*move the head and the body
 *input:if true,it means the body can go across the wall
 *output:true if the snake is dead(due to hit the wall or itself)
*/
bool Snake::move(bool ok)
{
	bool tail_flag = true; //indicate that if the tail is to be deleted
	/*insert the new head*/
	if (ok) //the head can go across the wall,so we use '%' to get the new pos
		body.push_front(pos((body[0].first + d[curdir][0] + NR_COL) % (NR_COL), (body[0].second + d[curdir][1] + NR_ROW) % (NR_ROW)));
	else
	{
		pos newpos = pos(body[0].first + d[curdir][0], body[0].second + d[curdir][1]);
		if (boundcheck(newpos)) //if the pos is legal,we set it as the new head
			body.push_front(newpos);
		else
			return true; //hit the wall
	}

	if (bodycheck())
		return true; //hit the body

	  /*if the head hit the food,the tail won't be deleted;
		moreover,change the head color if hit the 'Changecolor Food'*/

	int add; //the score got from the cur food
	if (add = foodcheck())
	{
		tail_flag = false;
		score += add;
		if (add > 1) //the 'Changecolor Food' will provide more than 1 points
			headcolor = HW_COLOR[RANDOM(0, NR_COLOR - 1)];
	}

	/*delete the tail pos if needed*/
	display(body.size() - 1, BK_COLOR); //trick,we set the old tail's color as the background color to 'delete' it
	vis[body.back().first][body.back().second] = NONE;
	if (!infty && tail_flag) //not in the infty mode,not hit the food
		body.pop_back();
	vis[body.front().first][body.front().second] = BODY_IN; //the old head now is the body

	display(0, headcolor);
	display(1, BODY_COLOR);
	return false;
}

/*
* output:true if the head hit the body
*/
bool Snake::bodycheck() const
{
	if (vis[body[0].first][body[0].second] == BODY_IN)
		return true;
	return false;
}

/*
* output:
* return NORMAL_FEEDBACK if the food is the normal one
* return SPECIAL_FEEDBACK if the food is the 'Change Color'one
*/
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

/*the func to change the cur dir of the Snake
* input:the keycode from the user's keyboard
* output:NULL
*/
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

/*default constructor*/
Food::Food()
{
	srand(time(NULL));
	int x, y;
	bool goon = true;
	/*set the first food's pos and draw it */
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
	cnt = 1; //the num of food has appeared until now
}

/*the func to draw
 * input :the pos to draw,the color to show
 * output:null
*/
void Food::display(pos _pos, COLORREF color) const
{
	setfillcolor(color);
	solidrectangle(_pos.first * COL_WIDTH, _pos.second * ROW_HEIGHT,
		_pos.first * COL_WIDTH + BODY_SIZE, (_pos.second) * ROW_HEIGHT + BODY_SIZE);
}

/*the logic to generate new food:
* if the cur food is common food,then we can't generate new food unless the time is out;
* if the cur food hasn't been eaten,we can't generate new food
*/
void Food::generate()
{
	/*the situation we can't generate food*/
	if ((Snake::vis[curpos.first][curpos.second] == SPECIAL_IN && isSpecial() && (--count >= 0)) || Snake::vis[curpos.first][curpos.second] == FOOD_IN && !isSpecial())
	{
		return;
	}
	/*delte the previous food*/
	if (isSpecial() && count <= 0) //use the trick to 'delete' the food
	{
		Snake::vis[curpos.first][curpos.second] = NONE;
		display(curpos, BK_COLOR);
	}
	cnt++; //the cnt to judge if the food to generate is special
	if (isSpecial())
	{
		count = STEPS;
	}
	/*randomly choose the pos until it's legal*/
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
	/*set the map status*/
	Snake::vis[x][y] = (isSpecial()) ? SPECIAL_IN : FOOD_IN;
	/*draw the food*/
	if (isSpecial())
		display(curpos, SPECIAL_FOOD_COLOR);
	else
		display(curpos, FOOD_COLOR);
}