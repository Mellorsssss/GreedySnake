#pragma once
#include <graphics.h>
#include <deque>
#include <utility>
#include <random>
#include <time.h>
#include <cstring>
#include "marco.h"
using namespace std;

class Snake;
class Food;
typedef pair<int, int>pos;

class Snake {
	friend class SnakeGame;
	friend class Food;
private:
	enum dir{ UP,DOWN,LEFT,RIGHT }curdir;
	deque<pos>body;
	COLORREF headcolor;
	void display(int i, COLORREF color)const;
	bool infty;//infty mode
	int score;
	static STATUS vis[NR_COL][NR_ROW];//true if the pos is visting
public:
	Snake();
	//~Snake();
	int length()const { return body.size(); };
	bool bodycheck()const;
	int foodcheck()const;
	bool boundcheck(pos a)const;
	bool move(bool ok);
	void changedir(char c);
};
//STATUS Snake::vis[NR_COL][NR_ROW] = {};

class Food {
	friend class SnakeGame;
	friend class Snake;
	private:
		pos curpos;
		int cnt;
		int count;
public:
	Food();
	~Food() {}
	void display(pos _pos, COLORREF color)const;
	void generate();
	bool isSpecial() { return (cnt % SPECIAL_TIME == 0); }
};

