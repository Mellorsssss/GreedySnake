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
	friend class Food;
private:
	enum dir{ UP,DOWN,LEFT,RIGHT }curdir;
	deque<pos>body;
	void display(int i, COLORREF color)const;
	bool infty;//infty mode
	bool vis[NR_COL][NR_ROW];//true if the pos is visting
public:
	Snake();
	//~Snake();
	void show()const;
	int length()const { return body.size(); };
	bool bodycheck()const;
	bool move();
	void changedir(char c);
};
