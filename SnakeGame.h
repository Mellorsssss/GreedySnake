#pragma once
#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "GreadySnake.h"
#include "marco.h"
#include <iostream>
#include <conio.h>
using namespace std;
char GAME_OVER_TIPS[] = "Hello World";
class SnakeGame {
private:
	Snake snake;
	Food food;
	double freq;
public:
	SnakeGame();
	//void init();
	void game();
	void putword(SIGNAL _sig)const;
	void showWall()const;
};

SnakeGame::SnakeGame() {
	freq = 0.1;
}

void SnakeGame::game() {
	initgraph(1000, 1000);
	setbkcolor(WHITE);   //set the 
	cleardevice();       //将背景颜色刷新到窗口上
	setfillcolor(BLACK); //设置填充的颜色为黑色，之后话填充的图形都是这个颜色
	setbkmode(TRANSPARENT);
	outtextxy(0,0, GAME_OVER_TIPS);
	food.generate();
	while (true) {
		Sleep(1000*0.1);
		if (snake.move())
		{
			cout << "you lose" << endl;
			putword(GAME_OVER);
			system("pause");
		}
		if (Snake::vis[food.curpos.first][food.curpos.second] == NONE)food.generate();
		char curkey='1';
		if(_kbhit()){
			curkey = _getch();
		}
		snake.changedir(curkey);
	}
}

void SnakeGame::putword(SIGNAL _sig)const {
	switch (_sig)
	{
	case GAME_OVER:
		outtextxy(CENTRAL_AREA, "over"); break;
	default:
		break;
	}
}

void SnakeGame::showWall()const {

}
#endif