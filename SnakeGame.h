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
	void game();
	void putword(SIGNAL _sig)const;
	void showWall()const;
	void showRecord()const;
};

SnakeGame::SnakeGame() {
	freq = 0.1;
}

void SnakeGame::game() {
	initgraph(1000, 1000);
	setbkcolor(WHITE);   //set the 
	cleardevice();       //将背景颜色刷新到窗口上
	setfillcolor(BLACK); //设置填充的颜色为黑色，之后话填充的图形都是这个颜色
	setbkmode(OPAQUE);
	setlinecolor(WALL_COLOR);
	settextcolor(WARNING_COLOR);
	outtextxy(0,0, GAME_OVER_TIPS);
	food.generate();
	showWall();
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
		showWall();
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
	line(0, 0, 0, HEIGHT);
	line(0, 0, BOARD, 0);
	line(0, HEIGHT, BOARD, HEIGHT);
	line(BOARD, HEIGHT, BOARD, 0);
}

void SnakeGame::showRecord()const {

}
#endif